#pragma once
#include <ECS.h>
#include <Globals.h>

namespace ECS
{
	namespace Systems
	{
		class ColorRotationPosSystem : public SystemBase
		{
			public:
				ColorRotationPosSystem(EntityManager* em) : SystemBase(em){};
				void run();
				void init();
		};
	}
}
