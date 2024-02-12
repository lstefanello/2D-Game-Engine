
#include <RenderSystem.h>
#include <KeyboardControlledSystem.h>
#include <AnimationSystem.h>
#include <ApplyVelocitySystem.h>
#include <CollisionSystem.h>
#include <ParticleSystem.h>
#include <DepthSystem.h>
#include <ColorRotationPosSystem.h>
#include <DestructSystem.h>
#include <ShootSystem.h>
#include <AttractorSystem.h>
#include <OffScreenDestroySystem.h>
#include <LightSourceSystem.h>
#include <CameraSystem.h>
#include <FrustumCullingSystem.h>
#include <FloatSystem.h>
#include <FollowSystem.h>

void ECS::SystemBase::add(unsigned int ID)
{
    entities.push_back(ID);
    id_to_slot[ID] = entities.size() - 1;
}

void ECS::SystemBase::del(unsigned int ID)
{
    int index = id_to_slot.at(ID);
    id_to_slot.erase(ID);
    entities.erase(entities.begin() + index);

    for (int i = 0; i < entities.size() - index; i++)
    {
        id_to_slot[entities[index + i]] -= 1;
    }
}

void ECS::SystemsManager::create_signatures(EntityManager* em)
{
    for (auto &system : system_order)
    {
        std::bitset<64> sig;
        
        for (auto &pool : system->required_pools)
        {
            int bit = em->type_to_pool_id.at(pool);
            sig.set(bit, true);
        }

        system->signature = sig;
    }
}

void ECS::SystemsManager::build_systems(EntityManager* em)
{
    system_order.push_back(std::make_unique<Systems::AnimationSystem>(em));
    system_order.push_back(std::make_unique<Systems::KeyboardControlledSystem>(em));
    system_order.push_back(std::make_unique<Systems::ShootSystem>(em));
    system_order.push_back(std::make_unique<Systems::ParticleSystem>(em));
    system_order.push_back(std::make_unique<Systems::AttractorSystem>(em));
    system_order.push_back(std::make_unique<Systems::FloatSystem>(em));
    system_order.push_back(std::make_unique<Systems::FollowSystem>(em));
    system_order.push_back(std::make_unique<Systems::ApplyVelocitySystem>(em));
    system_order.push_back(std::make_unique<Systems::CollisionSystem>(em));
    system_order.push_back(std::make_unique<Systems::CameraSystem>(em));
    system_order.push_back(std::make_unique<Systems::OffScreenDestroySystem>(em));
    system_order.push_back(std::make_unique<Systems::LightSourceSystem>(em));
    system_order.push_back(std::make_unique<Systems::DepthSystem>(em));
    system_order.push_back(std::make_unique<Systems::ColorRotationPosSystem>(em));
    system_order.push_back(std::make_unique<Systems::DestructSystem>(em));
    system_order.push_back(std::make_unique<Systems::FrustumCullingSystem>(em));    
    system_order.push_back(std::make_unique<Systems::RenderSystem>(em));    
}

void ECS::SystemsManager::init_systems()
{
    for (auto &system : system_order)
    {
        system->init();
    }
}

void ECS::SystemsManager::RunSystems()
{
    for (auto &system : system_order)
    {
        system->run();
    }
}
