#include <ParticleSystem.h>

void ECS::Systems::ParticleSystem::init()
{
    required_pools.push_back(typeid(ParticleEmitter));
    required_pools.push_back(typeid(Transform));

    t_pool = em->get_pool<Transform>();
    pe_pool = em->get_pool<ParticleEmitter>();
    phys_pool = em->get_pool<Physics>();
}

void ECS::Systems::ParticleSystem::run()
{
    for (auto &entity : entities)
    {
        auto* emitter_data = em->get_data(entity, pe_pool);

        if (emitter_data->is_active)
        {
            if (!emitter_data->timer.started)
            {
                emitter_data->timer.start();
            }

            auto* transform_data = em->get_data(entity, t_pool);

            float conversion = 1000.f * 1/emitter_data->particles_per_second;

            if (emitter_data->counter > emitter_data->particles_per_second - 1)
            {
                emitter_data->counter = 0;
                emitter_data->timer.stop();
                emitter_data->timer.start();
            }

            if (int(std::floor(emitter_data->timer.GetTime()/conversion)) > emitter_data->counter)
            {
                emitter_data->counter += 1;

                int ID = em->create();
                em->add<Transform>(ID);
                em->add<Physics>(ID);
                em->add<Destruct>(ID);
                em->add<Render>(ID);
                em->add<Depth>(ID);
                em->add<DynamicCollidable>(ID);
                em->add<Attractive>(ID);
                em->add<LightSource>(ID);

                auto* l_dat = em->get<LightSource>(ID);
                l_dat->radius = 0.3;
                l_dat->intensity = 3;
                l_dat->color = {1.0f, 0.75f, 0.0f, 1.0f};

                auto* particle_data = em->get_data(ID, t_pool);
                auto* particle_phys = em->get_data(ID, phys_pool);

                particle_data->scale = emitter_data->scale; 
                particle_data->colors = emitter_data->colors;
                particle_data->tex_coords = emitter_data->tex_coords; 

                particle_data->position.x = transform_data->position.x;
                particle_data->position.y = transform_data->position.y + 0.5f*transform_data->scale.y;

                particle_phys->velocity.x = 20 - (rand() % 40 + 0);
                particle_phys->velocity.y = rand() % 40 + 10;

            }
        }
    }
}
