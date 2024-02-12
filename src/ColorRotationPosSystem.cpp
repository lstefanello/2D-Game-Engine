#include <ColorRotationPosSystem.h>

void ECS::Systems::ColorRotationPosSystem::init()
{
    required_pools.push_back(typeid(Transform));
    required_pools.push_back(typeid(ColorRotationPos));
}

void ECS::Systems::ColorRotationPosSystem::run()
{
    for (auto &i : entities)
    {
        auto* tr_data = em->get<ECS::Transform>(i); 

        float color0 = tr_data->position.x / Globals::SCREEN_WIDTH; 
        float color1 = tr_data->position.y / Globals::SCREEN_HEIGHT; 

        tr_data->colors[0] = color0;
        tr_data->colors[1] = color1; 
        tr_data->colors[2] = (color0 + color1)/2;

        //tr_data->rotation = (tr_data->position.x * 2 * M_PI) / DisplayManager::SCREEN_WIDTH;
    }
}
