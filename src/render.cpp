#include "global.hpp"
#include <SDL2/SDL.h>


void render()
{
    SDL_RenderClear(rnd);



    SDL_RenderPresent(rnd);
}

