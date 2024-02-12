#pragma once
#include <ECS.h>

namespace ECS
{
	namespace Systems
	{
		class ApplyVelocitySystem : public SystemBase
		{
			public:
				ApplyVelocitySystem(EntityManager* em) : SystemBase(em){};
				void run();
				void init();

			private:
				ComponentPool<Transform>* t_pool;
				ComponentPool<Physics>* phys_pool;

				float GetFPS();

				Utilities::Timer timer;
				unsigned int frame_counter;
		};
	}
}
