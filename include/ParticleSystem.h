#pragma once
#include <ECS.h>

namespace ECS
{
	namespace Systems
	{
		class ParticleSystem : public SystemBase
		{
			public:
				ParticleSystem(EntityManager* em) : SystemBase(em){};
				void run();
				void init();
			private:
				ComponentPool<Transform>* t_pool;
				ComponentPool<ParticleEmitter>* pe_pool;
				ComponentPool<Physics>* phys_pool;
		};
	}
}
