#define GLEW_STATIC
#include <Main_State.h>
#include <DisplayManager.h>
#include <Globals.h>
#include <Utilities.h>

int main(int argc, char *argv[])
{
    DisplayManager::Window window("Engine", 0, 0, Globals::SCREEN_WIDTH, Globals::SCREEN_HEIGHT);
    DisplayManager::Initialize();
    DisplayManager::Texture spritesheet{"../resources/spriteatlas.png"};

    StateManager::Manager sm;
    sm.current_state = std::unique_ptr<StateManager::State>(new StateManager::Main_State());
    sm.state_id = StateManager::states::state_main;

    while(sm.state_id != StateManager::states::state_exit)
    {
        sm.current_state->Events(&sm);
        sm.change_state();
        sm.current_state->Logic();
        SDL_GL_SwapWindow(window.window);
    }

    SDL_GL_DeleteContext(window.context);
    SDL_DestroyWindow(window.window);
    SDL_Quit();
    return 0;
}
