#pragma once
#include <ECS.h>

namespace ECS
{
	namespace Systems
	{
		class ShootSystem : public SystemBase
		{
			public:
				ShootSystem(EntityManager* em) : SystemBase(em){};
				void run();
				void init();
		};
	}
}
