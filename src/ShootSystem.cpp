#include <ShootSystem.h>

void ECS::Systems::ShootSystem::init()
{
    required_pools.push_back(typeid(ECS::Shoot));
    required_pools.push_back(typeid(ECS::KeyboardControlled));
    required_pools.push_back(typeid(ECS::SoundEmitter));
    required_pools.push_back(typeid(ECS::Transform));
}

void ECS::Systems::ShootSystem::run()
{
    for (auto &entity : entities)
    {
        auto* proj_data = em->get<ECS::Shoot>(entity);
        auto* keyboard_data = em->get<ECS::KeyboardControlled>(entity);
        auto* transform_data = em->get<ECS::Transform>(entity);
        auto* sound_data = em->get<ECS::SoundEmitter>(entity);

        if (keyboard_data->space)
        {
            if (!proj_data->press)
            {
                proj_data->press = true;

                int projectile = em->create();
                em->add<ECS::Transform>(projectile);
                em->add<ECS::Physics>(projectile);
                em->add<ECS::Render>(projectile);
                em->add<ECS::Depth>(projectile);
                em->add<ECS::DynamicCollidable>(projectile);
//                em->add<ECS::ColorRotationPos>(projectile);
//                em->add<ECS::ParticleEmitter>(projectile);
                em->add<ECS::Attractive>(projectile);
                em->add<ECS::LightSource>(projectile);

                auto* l_dat = em->get<ECS::LightSource>(projectile);

                std::random_device rd;
                std::mt19937 gen(rd());
                std::uniform_real_distribution<> dis(0, 1);

                l_dat->intensity = 2.5f;
                l_dat->radius = 0.05f;
                l_dat->color = {dis(gen), dis(gen), dis(gen), 1.0f};

                while(sqrt(pow(l_dat->color.x,2) + pow(l_dat->color.y,2) + pow(l_dat->color.z,2)) < 0.75f)
                {
                    l_dat->color = {dis(gen), dis(gen), dis(gen), 1.0f};
                }
                

 //               auto* emitter_data = em->get<ParticleEmitter>(projectile);
  //              emitter_data->is_active = true;

                sound_data->buffered_sounds.push_back(ECS::SoundEmitter::Sounds::zap);
                
                auto* proj_transform = em->get<ECS::Transform>(projectile);
                auto* proj_physics = em->get<ECS::Physics>(projectile);

                proj_transform->position.x = transform_data->position.x + 0.5f*transform_data->scale.x + proj_data->padding;
                proj_transform->position.y = transform_data->position.y;

                proj_transform->scale = {13.0f, 13.0f};
                proj_transform->tex_coords = {6.0f, 4.0f, 13.0f, 13.0f};
                proj_transform->colors = {1.0f, 1.0f, 1.0f, 1.0f};

                if (transform_data->scale.x < 0)
                {
                    proj_physics->velocity.x = -200.0f;
                }
                else if (transform_data->scale.x > 0)
                {
                    proj_physics->velocity.x = 200.0f;
                }

                proj_physics->velocity.y = 0.0f;
            }
        }
        else
        {
            proj_data->press = false;
        }
    }
}
