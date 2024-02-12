#pragma once
#include <ECS.h>

namespace ECS
{
	namespace Systems
	{
		class FollowSystem : public SystemBase
		{
			public:
				FollowSystem(EntityManager* em) : SystemBase(em){};
				void run();
				void init();
			private:
				ComponentPool<Transform>* t_pool;
				ComponentPool<Physics>* p_pool;
				ComponentPool<Animated>* a_pool;
				ComponentPool<Follow>* f_pool;
		};
	}
}
