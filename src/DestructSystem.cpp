#include <DestructSystem.h>

void ECS::Systems::DestructSystem::init()
{
    required_pools.push_back(typeid(Destruct));
    required_pools.push_back(typeid(Transform));
}

void ECS::Systems::DestructSystem::run()
{
    auto copy = entities;

    for (auto &entity : copy)
    {
        auto* transform_data = em->get<ECS::Transform>(entity);
        auto* l_dat = em->get<LightSource>(entity);

        float factor = 0.01f;
        float colorfactor = 0.03f;

        transform_data->colors.w -= factor * transform_data->colors.w; 
        transform_data->colors.y -= colorfactor * transform_data->colors.y; 
        transform_data->scale.x -= factor * transform_data->scale.x;
        transform_data->scale.y -= factor * transform_data->scale.y;

        l_dat->radius += 2*factor * l_dat->radius;
        l_dat->intensity -= 2*factor * l_dat->intensity;

        if (transform_data->scale.x <= 1.0f)
        {
            em->destroy(entity);
        }
    }
}
