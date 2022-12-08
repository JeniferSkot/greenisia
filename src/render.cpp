#include "global.hpp"
#include <SDL2/SDL.h>
#include "player.hpp"
#include "map.hpp"


void render()
{
    SDL_SetRenderDrawColor(rnd, 0, 0, 0, 255);
    SDL_RenderClear(rnd);

    render_map();
    render_player();

    SDL_RenderPresent(rnd);
}

