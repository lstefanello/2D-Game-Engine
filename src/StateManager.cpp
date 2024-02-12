#include <StateManager.h>
#include <Game.h>
#include <Main_State.h>

using namespace StateManager;

Manager::Manager()
{
    next_state = states::state_null;
}

void Manager::queue_state(int state)
{
    next_state = state;
}

void Manager::change_state()
{
    if (next_state != states::state_null)
    {

        if (next_state != states::state_exit)
        {
           current_state.reset(); 
        }

        switch(next_state)
        {
            case states::state_game:
                current_state = std::unique_ptr<State>(new Game());
            break;

            case states::state_main:
                current_state = std::unique_ptr<State>(new Main_State());
            break;
        }

        state_id = next_state;
        next_state = states::state_null; 
    }
}
