#pragma once
#include <ECS.h>
#include <DisplayManager.h>

namespace ECS
{
	namespace Systems
	{
		class CameraSystem : public SystemBase
		{
			public:
				CameraSystem(EntityManager* em) : SystemBase(em){};
				void run();
				void init();

			private:
				int FindScaleFactor(int target_x, int target_y);
		};
	}
}
