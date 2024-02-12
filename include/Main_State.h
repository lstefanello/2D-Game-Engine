#pragma once
#include <StateManager.h>

namespace StateManager
{
	class Main_State : public State
	{
		public:
			Main_State();
			~Main_State();

			void Events(StateManager::Manager* sm);
			void Logic();
		
		private:
			int cursor;
			int ent;
	};
}
