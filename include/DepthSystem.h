#pragma once
#include <Globals.h>
#include <ECS.h>

namespace ECS
{
	namespace Systems
	{
		class DepthSystem : public SystemBase
		{
			public:
				DepthSystem(EntityManager* em) : SystemBase(em){};
				void run();
				void init();
		};
	}
}
