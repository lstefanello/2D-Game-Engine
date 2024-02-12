#include <DepthSystem.h>

void ECS::Systems::DepthSystem::init()
{
    required_pools.push_back(typeid(Transform));
    required_pools.push_back(typeid(Depth));
}

void ECS::Systems::DepthSystem::run()
{
    for (auto &entity : entities)
    {
        auto* transform_data = em->get<ECS::Transform>(entity);

//        transform_data->position.z = 1.0f * (Globals::SCREEN_HEIGHT - transform_data->position.y);
        transform_data->position.z = -1.0f*transform_data->position.y;
    }
}
