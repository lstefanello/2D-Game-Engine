#pragma once
#include <glm/glm.hpp>
#include <Utilities.h>

namespace ECS
{	
	struct SoundEmitter
	{
		enum Sounds
		{
			zap,
			walk,
			blip,
		};

		enum Music
		{
			none,
			good,
			home,
		};

		std::vector<int> buffered_sounds;
		int current_song{Music::none};

		Utilities::Timer timer;
	};

	struct Camera
	{
		glm::vec2 params;
		int scale_factor;
	};

	struct LightSource
	{
		float radius{0.03};
		float intensity;
		glm::vec4 color;
		Utilities::Timer timer;
	};

	struct OffScreenDestroy
	{
		Utilities::Timer timer;
	};

	struct Attractor
	{
		
	};

	struct Attractive
	{

	};

	struct StaticRender
	{

	};

	struct DynamicRender
	{

	};

	struct Render
	{

	};

	struct Transform
	{
		glm::vec4 colors;
		glm::vec4 tex_coords;
		glm::vec3 position; 
		glm::vec2 scale; 
		float rotation;
	};	

	struct Physics
	{
		glm::vec3 velocity;
		glm::vec3 initial_velocity;

		float x_acceleration{60.f};
		float y_acceleration{60.f};

		float x_deceleration{5.0f};
		float y_deceleration{5.0f};

		float max_x_velocity{100.0f};
		float max_y_velocity{100.0f};
	};

	struct KeyboardControlled
	{
		bool left{false};
		bool right{false};
		bool up{false};
		bool down{false};
		bool space{false};

		bool w{false};
		bool a{false};
		bool s{false};
		bool d{false};
	};

	struct ColorRotationPos
	{

	};

	struct StaticCollidable
	{

	};

	struct DynamicCollidable 
	{

	};

	enum anim_states 
	{
		idle,
		left,
		right,
		up,
		down,
		elephant_idle,
		elephant_walk,
		orb,
		big_orb,
		finn_idle,
		finn_walk,
		none
	};

	//maps an animation state to the coordinates in the texture atlas of first animation frame

	struct Animated
	{
		int rate{12};
		int current_state{anim_states::none};
		int next_state{anim_states::none};

//		int frame_counter{0};
		int current_frame{0};

		Utilities::Timer timer;
	};

	struct ParticleEmitter
	{
		bool is_active{true};

		int particles_per_second{20};
		int counter{0};

		glm::vec2 scale{13.0f, 13.0f};
		glm::vec4 colors{1.0f, 0.75f, 0.0f, 1.0f};
		glm::vec4 tex_coords{400.0f, 4.0f, 13.0f, 13.0f};

		Utilities::Timer timer;
	};

	struct Destruct
	{

	};

	struct FollowMouse
	{
		int grid_dim{32};
	};

	struct Depth
	{

	};

	struct Shoot
	{
		float padding{10.0f};

		bool press;
	};

	struct Float
	{
		float rate;
		Utilities::Timer timer;
	};

	struct Follow
	{
		unsigned int target_id;
	};
}
