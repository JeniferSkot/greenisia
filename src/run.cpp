#include "global.hpp"
#include <SDL2/SDL.h>

bool running = false;

void run()
{
    int last_tick = SDL_GetTicks();
    running = true;

    while(running) {
        int now = SDL_GetTicks();
        int progress = now - last_tick;
        last_tick = now;

        handle_events();
        tick(progress);
        render();
    }
}

