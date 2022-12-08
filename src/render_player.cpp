#include "global.hpp"
#include <SDL2/SDL.h>
#include "player.hpp"


void render_player()
{
    SDL_Rect player_area {
        player.pos.x,
        player.pos.y,
        player.size.x,
        player.size.y
    };

    SDL_SetRenderDrawColor(rnd, 0, 255, 0, 255);
    SDL_RenderFillRect(rnd, &player_area);
}
