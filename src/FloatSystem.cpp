#include <FloatSystem.h>

void ECS::Systems::FloatSystem::init()
{
    required_pools.push_back(typeid(Float));
    required_pools.push_back(typeid(Transform));

    t_pool = em->get_pool<Transform>();
    f_pool = em->get_pool<Float>();
}

void ECS::Systems::FloatSystem::run()
{
    for (auto &entity : entities)
    {
        auto t_data = em->get_data(entity, t_pool);
        auto f_data = em->get_data(entity, f_pool);

        if (!f_data->timer.started)
        {
            f_data->timer.start();
        }

        t_data->position.y += f_data->rate*sin(f_data->timer.GetTime()/1000.0f);
    }
}
