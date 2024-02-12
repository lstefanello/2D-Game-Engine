#pragma once
#include <ECS.h>

namespace ECS
{
	namespace Systems
	{
		void game_thread(PoolManager* pm);
		void update(PoolManager* pm);

/*	enum sys
	{
		transform_system,
		keyb_controlled_system,
		apply_velocity_system,
		color_rotation_pos_system,
		collision_system,
		animation_system,
		particle_system,
		destruct_system,
	};*/		
	}
}

