#include "render.hpp"
#include <SDL2/SDL.h>
#include "player.hpp"
#include "coin.hpp"
#include "map.hpp"
#include "background.hpp"
#include "level_editor/global.hpp"

namespace LE = level_editor;

void render()
{
    SDL_SetRenderDrawColor(rnd, 0, 0, 0, 255);
    SDL_RenderClear(rnd);

    render_background(-10, 0);
    render_player();
    render_coins();
    render_background(1, 10);
    render_coin_twinkles();

    if(show_debug_grid) {
        render_player_hitbox();
        render_map();
    }

    if(LE::active)
        LE::render();

    SDL_RenderPresent(rnd);
}

