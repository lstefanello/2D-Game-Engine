#include <KeyboardControlledSystem.h>

void ECS::Systems::KeyboardControlledSystem::init()
{
    required_pools.push_back(typeid(KeyboardControlled));
    required_pools.push_back(typeid(Physics));
    required_pools.push_back(typeid(Animated));
    required_pools.push_back(typeid(Transform));
    required_pools.push_back(typeid(SoundEmitter));
}

void ECS::Systems::KeyboardControlledSystem::run() 
{
    Utilities::InputHandler handler;
    handler.receive();

    for (auto &i : entities)
    {
        auto* k_data = em->get<ECS::KeyboardControlled>(i); 
        auto* p_data = em->get<ECS::Physics>(i); 
        auto* animated_data = em->get<ECS::Animated>(i); 
        auto* transform_data = em->get<ECS::Transform>(i); 
        auto* sound_data = em->get<ECS::SoundEmitter>(i);

        k_data->left = handler.flags.left;
        k_data->right = handler.flags.right;
        k_data->up = handler.flags.up;
        k_data->down = handler.flags.down;
        k_data->space = handler.flags.space;
        
        k_data->w = handler.flags.w;
        k_data->a = handler.flags.a;
        k_data->s = handler.flags.s;
        k_data->d = handler.flags.d;

        if (k_data->left || k_data->a)
        {
            p_data->velocity.y = 0;

            if (transform_data->scale.x > 0)
            {
                transform_data->scale.x *= -1;
            }

            p_data->velocity.x -= p_data->x_acceleration;
            animated_data->next_state = ECS::anim_states::right; 
            sound_data->buffered_sounds.push_back(ECS::SoundEmitter::Sounds::walk);
        }

        else if (k_data->right || k_data->d)
        {
            p_data->velocity.y = 0;

            if (transform_data->scale.x < 0)
            {
                transform_data->scale.x *= -1;
            }


            p_data->velocity.x += p_data->x_acceleration;
            animated_data->next_state = ECS::anim_states::right;
            sound_data->buffered_sounds.push_back(ECS::SoundEmitter::Sounds::walk);
        }

        else if (k_data->up || k_data->w)
        {
            p_data->velocity.x = 0;
            p_data->velocity.y -= p_data->y_acceleration;
            animated_data->next_state = ECS::anim_states::right;
            sound_data->buffered_sounds.push_back(ECS::SoundEmitter::Sounds::walk);
        }
        else if (k_data->down || k_data->s)
        {
            p_data->velocity.x = 0;
            p_data->velocity.y += p_data->y_acceleration;
            animated_data->next_state = ECS::anim_states::right;
            sound_data->buffered_sounds.push_back(ECS::SoundEmitter::Sounds::walk);
       }

        else
        {
            p_data->velocity.x > 0 ? p_data->velocity.x -= p_data->x_deceleration : p_data->velocity.x += p_data->x_deceleration;
            p_data->velocity.y > 0 ? p_data->velocity.y -= p_data->y_deceleration : p_data->velocity.y += p_data->y_deceleration; 

            if (std::abs(p_data->velocity.x) < 10.0f)
            {
                p_data->velocity.x = 0.0f;
                animated_data->next_state = ECS::anim_states::idle;
            }

            if (std::abs(p_data->velocity.y) < 10.0f)
            {
                p_data->velocity.y = 0.0f;
                animated_data->next_state = ECS::anim_states::idle;
            }

        }

        if (std::abs(p_data->velocity.x) >= p_data->max_x_velocity)
        {
            p_data->velocity.x > 0 ? p_data->velocity.x = p_data->max_x_velocity : p_data->velocity.x = -1.0f * p_data->max_x_velocity;
        }

        if (std::abs(p_data->velocity.y) >= p_data->max_x_velocity)
        {
            p_data->velocity.y > 0 ? p_data->velocity.y = p_data->max_y_velocity : p_data->velocity.y = -1.0f * p_data->max_y_velocity;
        }
    } 
}
