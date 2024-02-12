#include <FrustumCullingSystem.h>

void ECS::Systems::FrustumCullingSystem::init()
{
    required_pools.push_back(typeid(Transform));
    required_pools.push_back(typeid(StaticRender));

    t_pool = em->get_pool<Transform>();
    stat_r_pool = em->get_pool<StaticRender>();
    r_pool = em->get_pool<Render>();
    cam_pool = em->get_pool<Camera>();

    cell_width = 80;
    cell_height = 80;
    W = int(ceil(Globals::SCREEN_WIDTH/cell_width));
    H = int(ceil(Globals::SCREEN_HEIGHT/cell_height));
    static_map_created = false;

    for (int i = 0; i < (W+1)*(H+1); i++)
    {
        static_map.push_back(std::vector<int>());
    }
}

int ECS::Systems::FrustumCullingSystem::FindCell(float x, float y)
{
    return floor(x/cell_width) + floor(y/cell_height)*W;
}

void ECS::Systems::FrustumCullingSystem::BuildStaticMap()
{
   for (auto &i : entities)
   {
       auto position = em->get_data(i, t_pool)->position;
       static_map[FindCell(position.x, position.y)].push_back(i);
   }
   static_map_created = true;
}

int ECS::Systems::FrustumCullingSystem::FindCameraCell()
{
    auto camera = em->get_data(cam_pool->member_entities[0], cam_pool);
    cam_w = Globals::SCREEN_WIDTH/(2*camera->scale_factor);
    cam_h = Globals::SCREEN_HEIGHT/(2*camera->scale_factor);
    
    return FindCell(camera->params.x - cam_w, camera->params.y - cam_h);
}

void ECS::Systems::FrustumCullingSystem::FindVisibleCells(boost::unordered_set<int>* s)
{
    int cam_cell = FindCameraCell();
    int h = int(ceil(((2*cam_h)/cell_height)));
    int w = int(ceil(((2*cam_w)/cell_width)));

    for (int i = 0; i <= h; i++)
    {
        for (int j = 0; j <= w; j++) //j = -1 to render the column to the left of the view so that there is no pop-in on the left.
        {
            s->insert(cam_cell + i*W + j);
        }
    }
}

void ECS::Systems::FrustumCullingSystem::Compare(boost::unordered_set<int>* s)
{
    std::vector<int> sym_difference;

    std::set_symmetric_difference(s->begin(), s->end(), visible_cells.begin(), visible_cells.end(), std::back_inserter(sym_difference));

    for (auto &i : sym_difference)
    {
        if (s->count(i))
        {
            for (auto &j : static_map[i])
            {
                em->add<Render>(j);
            }
        }
        else
        {
            for (auto &j : static_map[i])
            {
                em->del<Render>(j);
            }
        }
    }
}

void ECS::Systems::FrustumCullingSystem::run()
{
    if (!static_map_created)
    {
        BuildStaticMap();
    }

    boost::unordered_set<int> current_cells;
    FindVisibleCells(&current_cells);
    Compare(&current_cells);
    visible_cells = current_cells;
}
