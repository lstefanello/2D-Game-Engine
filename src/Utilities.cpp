#include <Utilities.h>

void Utilities::InputHandler::receive()
{
    c_keystates = SDL_GetKeyboardState(NULL);
    std::vector<int> keycode = {SDL_SCANCODE_LEFT, SDL_SCANCODE_RIGHT, SDL_SCANCODE_UP, SDL_SCANCODE_DOWN, SDL_SCANCODE_SPACE, SDL_SCANCODE_W, SDL_SCANCODE_A, SDL_SCANCODE_S, SDL_SCANCODE_D, SDL_SCANCODE_P};

    for (auto &i : keycode)
    {
        bool* input;

        switch(i)
        {
            case SDL_SCANCODE_LEFT:
                input = &flags.left;
            break;
            case SDL_SCANCODE_RIGHT:
                input = &flags.right;
            break;
            case SDL_SCANCODE_UP:
                input = &flags.up;
            break;
            case SDL_SCANCODE_DOWN:
                input = &flags.down;
            break;
            case SDL_SCANCODE_SPACE:
                input = &flags.space;
            break;
            case SDL_SCANCODE_W:
                input = &flags.w;
            break;
            case SDL_SCANCODE_A:
                input = &flags.a;
            break;
            case SDL_SCANCODE_S:
                input = &flags.s;
            break;
            case SDL_SCANCODE_D:
                input = &flags.d;
            break;
            case SDL_SCANCODE_P:
                input = &flags.p;
            break;
        }

        (c_keystates[i]) ? (*input = true) : (*input = false);
    }
}

Utilities::Timer::Timer()
{
   start_time = 0;
   started = false;
}

void Utilities::Timer::start()
{
   started = true;
   start_time = SDL_GetTicks();
}

void Utilities::Timer::stop()
{
   started = false;
}

Uint32 Utilities::Timer::GetTime()
{
   Uint32 time = 0;

   if (started)
   {
       time = SDL_GetTicks() - start_time;
   }

   return time;
}
