#include <CountDestroySystem.h>

void ECS::Systems::CountDestroy::CountDestroySystem(PoolManager* pm)
{
    auto copy = pm->get_pool<ECS::CountDestroy>()->member_entities;
    for (auto entity : copy)
    {
        auto* data = pm->get<ECS::CountDestroy>(entity);
        data->count += 1;

        if (data->count >= 60*10)
        {
            pm->destroy(entity);
        }
    }
}
