#include <ApplyVelocitySystem.h>

void ECS::Systems::ApplyVelocitySystem::init()
{
    required_pools.push_back(typeid(Transform));
    required_pools.push_back(typeid(Physics));

    t_pool = em->get_pool<Transform>();
    phys_pool = em->get_pool<Physics>();

    frame_counter = 0;
    timer.start();
}

float ECS::Systems::ApplyVelocitySystem::GetFPS()
{
    float fps;

    if (timer.GetTime()/1000 > 0.0f)
    {
        fps = frame_counter/(timer.GetTime()/1000);
    }
    else
    {
        fps = 60.0f;
    }

    frame_counter++;

    return fps;
}

void ECS::Systems::ApplyVelocitySystem::run() 
{
//    float fps = GetFPS();

    for (auto &i : entities)
    {
        auto* tr_data = em->get_data(i, t_pool);
        auto* p_data = em->get_data(i, phys_pool); 

        tr_data->position.x += p_data->velocity.x * 1/60.0f;
        tr_data->position.y += p_data->velocity.y * 1/60.0f;
    }
}
