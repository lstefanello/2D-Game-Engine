#pragma once
#include <Utilities.h>
#include <ECS.h>

namespace ECS
{
	namespace Systems
	{
		class FollowMouseSystem : public SystemBase
		{
			public:
				FollowMouseSystem(EntityManager* em) : SystemBase(em){};
				void run();
				void init();
		};
	}
}
