#include <AttractorSystem.h>
#include <math.h>

void ECS::Systems::AttractorSystem::init()
{
    required_pools.push_back(typeid(Transform));
    required_pools.push_back(typeid(Physics));
    required_pools.push_back(typeid(Attractor));
}

void ECS::Systems::AttractorSystem::run() 
{
    auto attractives = em->get_pool<Attractive>()->member_entities;

    float g = 1.5f;

    for (auto &i : entities)
    {
        auto* trans_data = em->get<Transform>(i);
        auto x = trans_data->position.x;
        auto y = trans_data->position.y;
        auto m_1 = trans_data->scale.x * trans_data->scale.y;

        for (auto &j : attractives)
        {
            auto* attr_trans_data = em->get<Transform>(j);
            auto* attr_physics_data= em->get<Physics>(j);
            auto a_x = attr_trans_data->position.x;
            auto a_y = attr_trans_data->position.y;
            auto m_2 = attr_trans_data->scale.x * attr_trans_data->scale.y;

            float r = sqrt((x - a_x)*(x - a_x) + (y - a_y)*(y - a_y));

            float force = g*((m_1*m_2)/(r*r));

            glm::vec2 force_vector = glm::vec2{((x - a_x)/r)*force, ((y - a_y)/r)*force}; 

            if (force < 200.0f)
            {
               attr_physics_data->velocity += glm::vec3(force_vector.x, force_vector.y, 0.0f); 
            }
        }
    }
}
