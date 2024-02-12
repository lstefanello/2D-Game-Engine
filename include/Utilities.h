#pragma once
#include <vector>
#include <SDL2/SDL.h>
#include <glm/glm.hpp>
#include <Globals.h>

namespace Utilities
{
	class InputHandler
	{
		public:
			struct Flags
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
				bool p{false};
			} flags;

			void receive();
		private:
			const Uint8* c_keystates;
	};

	 class Timer
   {
		 public:
			 Timer();

			 Uint32 start_time;
			 Uint32 GetTime();

			 void start();
			 void stop();

			 bool started;
   };
}
