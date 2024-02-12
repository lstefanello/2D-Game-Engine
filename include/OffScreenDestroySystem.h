#pragma once
#include <ECS.h>

namespace ECS
{
	namespace Systems
	{
		class OffScreenDestroySystem : public SystemBase
		{
			public:
				OffScreenDestroySystem(EntityManager* em) : SystemBase(em){};
				void run();
				void init();
		};
	}
}
