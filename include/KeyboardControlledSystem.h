#pragma once
#include <Utilities.h>
#include <ECS.h>

namespace ECS
{
	namespace Systems
	{
		class KeyboardControlledSystem : public SystemBase
		{
			public:
				KeyboardControlledSystem(EntityManager* em) : SystemBase(em){};
				void run();
				void init();
		};
	}
}
