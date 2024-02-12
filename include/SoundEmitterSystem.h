#pragma once
#include <ECS.h>
#include <SDL_mixer.h>

namespace ECS
{
	namespace Systems
	{
		class SoundEmitterSystem : public SystemBase
		{
			public:
				SoundEmitterSystem(EntityManager* em) : SystemBase(em){};
				~SoundEmitterSystem();
				void run();
				void init();
			private:
				Mix_Chunk* GetSound(int sound);
				Mix_Music* GetMusic(int music);

				Mix_Music* good;
				Mix_Music* home;

				Mix_Chunk* walk;
				Mix_Chunk* zap;
				Mix_Chunk* blip;
		};
	}
}
