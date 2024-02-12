#pragma once
#include <ECS.h>
#include <DisplayManager.h>

namespace ECS
{
	namespace Systems
	{
		class LightSourceSystem : public SystemBase
		{
			public:
				LightSourceSystem(EntityManager* em) : SystemBase(em){};
				void run();
				void init();
		};
	}
}
