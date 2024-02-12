#include <OffScreenDestroySystem.h>

void ECS::Systems::OffScreenDestroySystem::init()
{
    required_pools.push_back(typeid(Transform));
    required_pools.push_back(typeid(OffScreenDestroy));
}

void ECS::Systems::OffScreenDestroySystem::run() 
{
    auto copy = entities;
    auto cam = em->get_pool<Camera>()->member_entities[0];
    auto* cam_dat = em->get<Transform>(cam);

    for (auto &i : copy)
    {
        auto* t_dat = em->get<Transform>(i);
        auto* d_data = em->get<OffScreenDestroy>(i);

        float x = t_dat->position.x;
        float y = t_dat->position.y;
        float x_w = t_dat->scale.x;
        float x_h = t_dat->scale.y;

        if (x < (cam_dat->position.x - Globals::SCREEN_WIDTH/2 - x_w) ||
             x > (cam_dat->position.x + Globals::SCREEN_WIDTH/2 + x_w) || 
             y < (cam_dat->position.y - Globals::SCREEN_HEIGHT/2 - x_h) ||
             y > (cam_dat->position.y + Globals::SCREEN_HEIGHT/2 + x_h))
        { 
        
            if(!d_data->timer.started)
            {
                d_data->timer.start();
            }

            if(d_data->timer.GetTime() > 5000)
            {
                em->destroy(i);
            }

            em->del<Render>(i);
        }
        else
        {
            if(d_data->timer.started)
            {
                d_data->timer.stop();
                em->add<Render>(i);
            }
        }
    }
}
