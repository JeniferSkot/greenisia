#include "render.hpp"
#include <SDL2/SDL.h>
#include "player.hpp"
#include "map.hpp"
#include "background.hpp"


void render()
{
    SDL_SetRenderDrawColor(rnd, 0, 0, 0, 255);
    SDL_RenderClear(rnd);

    render_background(-10, 0);
    render_player();
    render_background(1, 10);

    render_map();

    SDL_RenderPresent(rnd);
}

