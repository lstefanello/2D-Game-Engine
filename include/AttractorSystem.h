#pragma once
#include <ECS.h>

namespace ECS
{
	namespace Systems
	{
		class AttractorSystem : public SystemBase
		{
			public:
				AttractorSystem(EntityManager* em) : SystemBase(em){};
				void run();
				void init();
		};
	}
}
