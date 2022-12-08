#include "global.hpp"
#include <SDL2/SDL.h>
#include "Player.hpp"


void render()
{
    SDL_SetRenderDrawColor(rnd, 0, 0, 0, 255);
    SDL_RenderClear(rnd);


    SDL_Rect player_area {
        player.pos.x,
        player.pos.y,
        player.size.x,
        player.size.y
    };

    SDL_SetRenderDrawColor(rnd, 0, 255, 0, 255);
    SDL_RenderFillRect(rnd, &player_area);


    SDL_RenderPresent(rnd);
}

