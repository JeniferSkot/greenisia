#include "global.hpp"
#include <SDL2/SDL.h>


void run()
{
    int last_tick = SDL_GetTicks();

    while(true) {
        int now = SDL_GetTicks();
        int progress = now - last_tick;
        last_tick = now;

        handle_events();
        tick(progress);
        render();
    }
}

