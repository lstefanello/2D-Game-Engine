#pragma once
#include <ECS.h>

namespace ECS
{
	namespace Systems
	{
		class AnimationSystem : public SystemBase
		{
			public:
				AnimationSystem(EntityManager* em) : SystemBase(em){};
				void run();
				void init();
			private:
				float distance_between_frames;

				boost::unordered_map<int, float> state_to_x;
				boost::unordered_map<int, float> state_to_y;
				boost::unordered_map<int, int> state_to_length;
				boost::unordered_map<int, int> distance; 
		};
	}
}
