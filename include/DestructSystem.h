#pragma once
#include <ECS.h>

namespace ECS
{
	namespace Systems
	{
		class DestructSystem : public SystemBase
		{
			public:
				DestructSystem(EntityManager* em) : SystemBase(em){};
				void run();
				void init();
		};
	}
}
