#include "global.hpp"
#include <SDL2/SDL.h>


void handle_events()
{
    SDL_Event ev;
    while(SDL_PollEvent(&ev)) {
        switch(ev.type) {

        case SDL_QUIT:
            running = false;
            break;

        }
    }
}

