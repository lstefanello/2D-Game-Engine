#include <AnimationSystem.h>

void ECS::Systems::AnimationSystem::init()
{
    required_pools.push_back(typeid(Animated));
    required_pools.push_back(typeid(Transform));

    state_to_x = 
    {
        {ECS::anim_states::idle, 4.0f},
        {ECS::anim_states::finn_idle, 18.0f},
        {ECS::anim_states::finn_walk, 306.0f},
        {ECS::anim_states::right, 76.0f},
        {ECS::anim_states::elephant_idle, 263.0f},
        {ECS::anim_states::elephant_idle, 263.0f},
        {ECS::anim_states::orb, 20.0f},
        {ECS::anim_states::big_orb, 3.0f},
    };

    state_to_y =
    {
        {ECS::anim_states::idle, 64.0f},
        {ECS::anim_states::finn_idle, 389.0f},
        {ECS::anim_states::finn_walk, 388.0f},
        {ECS::anim_states::right, 64.0f},
        {ECS::anim_states::elephant_idle, 190.0f},
        {ECS::anim_states::orb, 263.0f},
        {ECS::anim_states::big_orb, 334.0f},
    };

    state_to_length = 
    {
        {ECS::anim_states::idle, 4},
        {ECS::anim_states::finn_idle, 9},
        {ECS::anim_states::finn_walk, 7},
        {ECS::anim_states::right, 7},
        {ECS::anim_states::elephant_idle, 4},
        {ECS::anim_states::orb, 8},
        {ECS::anim_states::big_orb, 8},
    };

    distance = 
    {
        {ECS::anim_states::idle, 24},
        {ECS::anim_states::finn_idle, 32},
        {ECS::anim_states::finn_walk, 32},
        {ECS::anim_states::right, 24},
        {ECS::anim_states::elephant_idle, 4},
        {ECS::anim_states::orb, 64},
        {ECS::anim_states::big_orb, 64},
    };
}

void ECS::Systems::AnimationSystem::run()
{

    for (auto &entity : entities)
    {
        auto* a_data = em->get<Animated>(entity);
        auto* t_data = em->get<Transform>(entity);
        
        if (a_data->next_state != anim_states::none)
        {
            if (a_data->current_state != a_data->next_state)
            {
                a_data->current_state = a_data->next_state;

                if(a_data->timer.started)
                {
                    a_data->timer.stop();
                }

                a_data->timer.start();

            }

            a_data->next_state = anim_states::none;
        }
        
        distance_between_frames = distance.at(a_data->current_state);
        float x = state_to_x.at(a_data->current_state);
        float y = state_to_y.at(a_data->current_state);

        a_data->current_frame = int(std::floor(a_data->timer.GetTime() / 83.333f)) % state_to_length.at(a_data->current_state);

        //std::cout << a_data->current_frame << std::endl;

        t_data->tex_coords.x = x + (a_data->current_frame * distance_between_frames);
        t_data->tex_coords.y = y;
    }
}
