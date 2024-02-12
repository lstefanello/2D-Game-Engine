#include <FollowSystem.h>

void ECS::Systems::FollowSystem::init()
{
    required_pools.push_back(typeid(Transform));
    required_pools.push_back(typeid(Physics));
    required_pools.push_back(typeid(Animated));
    required_pools.push_back(typeid(Follow));

    t_pool = em->get_pool<Transform>();
    p_pool = em->get_pool<Physics>();
    a_pool = em->get_pool<Animated>();
    f_pool = em->get_pool<Follow>();
}

void ECS::Systems::FollowSystem::run()
{
    for (auto &entity : entities)
    {
        auto f_dat = em->get_data(entity, f_pool);
        auto t_dat = em->get_data(entity, t_pool);
        auto a_dat = em->get_data(entity, a_pool);
        auto p_dat = em->get_data(entity, p_pool);
        auto target_transform = em->get_data(f_dat->target_id, t_pool);

        glm::vec2 diff = {target_transform->position.x - t_dat->position.x, target_transform->position.y - t_dat->position.y};

        if (sqrt(pow(target_transform->position.x - t_dat->position.x, 2) + pow(target_transform->position.y - t_dat->position.y, 2)) > 40.0f)
        {
           p_dat->velocity.x += (1/5.0f) * diff.x;
           p_dat->velocity.y += (1/5.0f) * diff.y;
           a_dat->next_state = ECS::anim_states::finn_walk;
        }
        else
        {
            p_dat->velocity.x = 0; 
            p_dat->velocity.y = 0; 
            a_dat->next_state = ECS::anim_states::finn_idle;
        }

        if (abs(p_dat->velocity.x) > 100.0f)
        {
            p_dat->velocity.x = p_dat->velocity.x/abs(p_dat->velocity.x) * 100.0f;
        }

        if (abs(p_dat->velocity.y) > 100.0f)
        {
            p_dat->velocity.y = p_dat->velocity.y/abs(p_dat->velocity.y) * 100.0f;
        }

        if (diff.x < 0)
        {
            if (t_dat->scale.x > 0)
            {
                t_dat->scale.x *= -1;
            }
        }
        else
        {
            t_dat->scale.x = abs(t_dat->scale.x);
        }
    }
}
