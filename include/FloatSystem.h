#pragma once
#include <ECS.h>

namespace ECS
{
	namespace Systems
	{
		class FloatSystem : public SystemBase
		{
			public:
				FloatSystem(EntityManager* em) : SystemBase(em){};
				void run();
				void init();

			private:
				ComponentPool<Transform>* t_pool;
				ComponentPool<Float>* f_pool;
		};
	}
}
