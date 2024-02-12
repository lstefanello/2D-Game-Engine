#include <FollowMouseSystem.h>

void ECS::Systems::FollowMouseSystem::init()
{
    required_pools.push_back(typeid(FollowMouse));
    required_pools.push_back(typeid(Transform));
}

void ECS::Systems::FollowMouseSystem::run() 
{
    int x, y;
    SDL_GetMouseState(&x, &y);

    for (auto &i : entities)
    {
        auto* t_data = em->get<Transform>(i);

        t_data->position.x = x;
        t_data->position.y = y;
    }

/*    int x_id = int(std::floor(x/32.0f));
    int y_id = int(std::floor(y/32.0f));

    for (auto &i : entities)
    {
        auto t_data = em->get<Transform>(i);

        t_data->position.x = x_id*32.0f + 16.0f;
        t_data->position.y = y_id*32.0f + 16.0f;
    }*/
}
