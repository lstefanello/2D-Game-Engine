#include <CollisionSystem.h>

//this is gonna be broken bc doesn't account for negative scale

void ECS::Systems::CollisionSystem::init()
{
    required_pools.push_back(typeid(Transform));
    required_pools.push_back(typeid(Physics));
    required_pools.push_back(typeid(StaticCollidable));
}

int ECS::Systems::CollisionSystem::GetCellID(std::pair<float, float> vertex)
{
    int length = ceil(Globals::SCREEN_WIDTH / cell_dim);
    int cell_x = std::floor(vertex.first / cell_dim);
    int cell_y = std::floor(vertex.second / cell_dim);
    int cell_ID = cell_x + (length * cell_y);

    return cell_ID;
}

void ECS::Systems::CollisionSystem::AddToStaticCell(int ID, std::pair<float, float> vertex)
{
    int cell_ID = GetCellID(vertex);
    
    if (cell_ID >= 0 && cell_ID <= num_cells)
    {
        if (!static_member_cells[ID][cell_ID])
        {
            static_member_cells[ID][cell_ID] = true;
            static_hmap[cell_ID].push_back(ID); 
        }
    }
}

void ECS::Systems::CollisionSystem::AddToDynamicCell(int ID, std::pair<float, float> vertex)
{
    int cell_ID = GetCellID(vertex);
    
    if (cell_ID >= 0 && cell_ID <= num_cells)
    {
        if (!dynamic_member_cells[ID][cell_ID])
        {
            dynamic_member_cells[ID][cell_ID] = true;
            dynamic_hmap[cell_ID].push_back(ID);
            key[ID].push_back(cell_ID);
        }
    }
}

std::array<std::pair<float, float>, 4> ECS::Systems::CollisionSystem::GetVertices(int ID)
{
    auto* tr_data = pman->get<Transform>(ID);

    auto x = tr_data->position.x;
    auto y = tr_data->position.y;

    float x_1 = x - abs(tr_data->scale[0])*0.5f;
    float y_1 = y + abs(tr_data->scale[1])*0.5f;

    float x_2 = x + abs(tr_data->scale[0])*0.5f;
    float y_2 = y + abs(tr_data->scale[0])*0.5f;

    float x_3 = x + abs(tr_data->scale[0])*0.5f;
    float y_3 = y - abs(tr_data->scale[1])*0.5f;

    float x_4 = x - abs(tr_data->scale[0])*0.5f;
    float y_4 = y - abs(tr_data->scale[1])*0.5f;

    return std::array<std::pair<float, float>, 4>{std::make_pair(x_1, y_1), std::make_pair(x_2, y_2), std::make_pair(x_3, y_3), std::make_pair(x_4, y_4)};
}
void ECS::Systems::CollisionSystem::BuildDynamicHashMap()
{
    for (auto &i : pman->get_pool<DynamicCollidable>()->member_entities)
    {
        dynamic_member_cells[i] = std::vector<bool>(num_cells, false);

        auto verts = GetVertices(i);
        
        for (int j = 0; j < 4; j++)
        {
            AddToDynamicCell(i, verts[j]);
        }
    }
}

void ECS::Systems::CollisionSystem::BuildStaticHashMap()
{
    static_hashmap_built = true;

    for (auto &i : pman->get_pool<StaticCollidable>()->member_entities)
    {
        static_member_cells[i] = std::vector<bool>(num_cells, false);

        auto verts = GetVertices(i);
        
        for (int j = 0; j < 4; j++)
        {
            AddToStaticCell(i, verts[j]);
        }
    }
}

void ECS::Systems::CollisionSystem::DetectCollisions()
{
    for (auto &i : pman->get_pool<DynamicCollidable>()->member_entities) //check dynamic collidables against static collidables
    {
        auto A = pman->get<Transform>(i); 
        
        for (auto &cell_ID : key[i])//loop through every cell the entity is a member of 
        {
            for (auto &entity : static_hmap[cell_ID])
            {
                auto B = pman->get<Transform>(entity); 

                if (B->position.x + 0.5f*abs(B->scale[0]) > A->position.x - 0.5f*abs(A->scale[0]) && 
                    B->position.x - 0.5f*abs(B->scale[0]) < A->position.x + 0.5f*abs(A->scale[0]) && 
                    B->position.y - 0.5f*abs(B->scale[1]) < A->position.y + 0.5f*abs(A->scale[1]) && 
                    B->position.y  + 0.5f*abs(B->scale[1]) > A->position.y - 0.5f*abs(A->scale[1]))
                {
                    static_dynamic_collisions.push_back(std::make_pair(i, entity)); //dynamic entity will always be first in the pair                                                                    //
                }
            }
        }
    }
}
/* auto copy = h_map[i];
        for (int j = 0; j < h_map[i].size(); j++) //loop by index so we can delete by index
        {
            auto A = tr_pool->data[tr_pool->key.at(h_map[i][j])];
            copy.erase(copy.begin() + 0);

            for (auto &k : copy)
            {
                auto B = tr_pool->data[tr_pool->key.at(k)];

                if (B.position.x + 0.5f*B.scale[0] > A.position.x - 0.5f*A.scale[0] && 
                    B.position.x - 0.5f*B.scale[0] < A.position.x + 0.5f*A.scale[0] && 
                    B.position.y - 0.5f*B.scale[1] < A.position.y + 0.5f*A.scale[1] && 
                    B.position.y  + 0.5f*B.scale[1] > A.position.y - 0.5f*A.scale[1])
                {
                    colliding_entities.push_back(std::make_pair(h_map[i][j], k));
                }
            }
        }*/
//}

void ECS::Systems::CollisionSystem::ResolveCollisions()
{
    for (auto &i : static_dynamic_collisions)
    {
        int static_ent = i.second;
        int dynamic_ent = i.first;

        auto* static_tr = pman->get<Transform>(static_ent);
        auto* dynamic_tr  = pman->get<Transform>(dynamic_ent); 
        auto* static_phys = pman->get<Physics>(static_ent);
        auto* dynamic_phys = pman->get<Physics>(dynamic_ent); 

        float x_diff = dynamic_tr->position.x - static_tr->position.x;
        float y_diff = dynamic_tr->position.y - static_tr->position.y;
        
        /* The strategy here is to cut the static quad into triangles, draw a line between the centers of the static and dynamic quads, and see which triangle the line falls inside. Then we'll know how to resolve the collision*/

        float theta = std::asin(y_diff / (std::sqrt(std::pow(x_diff, 2) + std::pow(y_diff, 2))));//the angle of the line drawn between the centers of the two quads
        float gamma = std::asin(static_tr->scale.y / std::sqrt(std::pow(static_tr->scale.x, 2) + std::pow(static_tr->scale.y, 2)));
        float phi = M_PI - gamma;

        if (theta < gamma && theta > -1 * gamma)
        {
            dynamic_phys->velocity.x = 0;
            dynamic_phys->velocity.y *= 0.1f;

            if (dynamic_tr->position.x > static_tr->position.x)
            {
                dynamic_tr->position.x = (static_tr->position.x + 0.5f*abs(static_tr->scale[0])) + 0.5f*abs(dynamic_tr->scale[0]);
            }
            else
            {
                dynamic_tr->position.x = (static_tr->position.x - 0.5f*abs(static_tr->scale[0])) - 0.5f*abs(dynamic_tr->scale[0]);
            }
        }
        else if (theta > gamma  && theta < phi)
        {
            dynamic_phys->velocity.y = 0;
            dynamic_phys->velocity.x *= 0.1f;
            dynamic_tr->position.y = (static_tr->position.y + 0.5f*abs(static_tr->scale[1])) + 0.5f*abs(dynamic_tr->scale[1]);
        }
        else if (-1 * theta > gamma && -1 * theta < phi)
        {
            dynamic_phys->velocity.y = 0;
            dynamic_phys->velocity.x *= 0.1f;
            dynamic_tr->position.y = (static_tr->position.y - 0.5f*abs(static_tr->scale[1])) - 0.5f*abs(dynamic_tr->scale[1]);
        }
    }
}

void ECS::Systems::CollisionSystem::run()
{
    cell_dim = 80;
    num_cells = int(ceil((Globals::SCREEN_WIDTH/cell_dim))*ceil((Globals::SCREEN_HEIGHT/cell_dim)));

    pman = em;

    dynamic_hmap.clear();
    key.clear();
    static_dynamic_collisions.clear();
    
    if(!static_hashmap_built)
    {
        BuildStaticHashMap();
    }

    BuildDynamicHashMap();
    DetectCollisions();
    ResolveCollisions();
}
