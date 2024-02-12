#pragma once
#include <Globals.h>
#include <ECS.h>
#include <DisplayManager.h>

namespace ECS
{
	namespace Systems
	{
		class RenderSystem : public SystemBase
		{
			public:
				RenderSystem(EntityManager* em) : SystemBase(em){};
				void run();
				void init();

			private:
				ECS::ComponentPool<Transform>* t_data;
				Utilities::Timer timer;
		};
	}
}
