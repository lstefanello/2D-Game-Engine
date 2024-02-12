#pragma once
#include <DisplayManager.h>
#include <ECS.h>
#include <Text.h>
#include <Globals.h>
#include <Utilities.h>

using namespace ECS;

namespace StateManager
{
	enum states
	{
		state_null,
		state_exit,
		state_game,
		state_main
	};
	
	class Manager;
	class State
	{
		public:
			virtual ~State(){};
			virtual void Events(Manager* sm) = 0;
			virtual void Logic() = 0;
			SDL_Event event;

		protected:
			EntityManager em;
	};

	class Manager
	{
		public:
			Manager();
			void queue_state(int state);
			void change_state();
			std::unique_ptr<State> current_state;
			int state_id;
		private:
			int next_state;
	};
}
