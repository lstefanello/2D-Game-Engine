#include <ECS.h>

ECS::EntityManager::EntityManager()
{
    entity_id_counter = 0;
    pool_id_counter = 0;

    create_pool<FollowMouse>();
    create_pool<Transform>();
    create_pool<Render>();
    create_pool<StaticRender>();
    create_pool<DynamicRender>();
    create_pool<Physics>();
    create_pool<KeyboardControlled>();
    create_pool<ColorRotationPos>();
    create_pool<StaticCollidable>();
    create_pool<DynamicCollidable>();
    create_pool<Animated>();
    create_pool<ParticleEmitter>();
    create_pool<Destruct>();
    create_pool<Depth>();
    create_pool<Shoot>();
    create_pool<Attractor>();
    create_pool<Attractive>();
    create_pool<OffScreenDestroy>();
    create_pool<LightSource>();
    create_pool<Camera>();
    create_pool<SoundEmitter>();
    create_pool<Float>();
    create_pool<Follow>();
    
    sm.build_systems(this);
    sm.init_systems();
    sm.create_signatures(this);
}

int ECS::EntityManager::create()
{
    int ID;
    
    if (!free_ids.empty())
    {
        ID = free_ids.back();
        free_ids.erase(free_ids.end() - 1);
    }
    else
    {
        ID = entity_id_counter;
        entity_id_counter++;
    }

    ent_id_to_components[ID] = std::bitset<64>();

    return ID;
}

void ECS::EntityManager::destroy(unsigned int ID)
{
    auto* comp_bitset = &ent_id_to_components[ID];

    for (int i = 0; i < pool_id_counter; i++)
    {
        if (comp_bitset->test(i))
        {
            pool_id_to_mem_address[i]->rem(ID);
            comp_bitset->set(i, false);
        }
    }

    notify(1, ID);
    ent_id_to_components.erase(ID);
    free_ids.push_back(ID);
}

std::bitset<64> ECS::EntityManager::fetch_components(unsigned int ID)
{
    return ent_id_to_components[ID];
}


void ECS::EntityManager::run_systems()
{
    sm.RunSystems();
}

void ECS::EntityManager::notify(int action, unsigned int ID)
{
    switch(action)
    {
        case 0: //add
            for (auto &system : sm.system_order)
            {
                if ((fetch_components(ID) & system->signature) == system->signature)
                {
                    if (system->id_to_slot.count(ID) == 0)
                    {
                        system->add(ID);
                    }
                }
            }
        break;

        case 1: //delete
            for (auto &system : sm.system_order)
            {
                if ((fetch_components(ID) & system->signature) != system->signature)
                {
                    if (system->id_to_slot.count(ID) != 0)
                    {
                        system->del(ID);
                    }
                }
            }
        break;
    }
}
