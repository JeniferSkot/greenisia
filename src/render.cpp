#include "render.hpp"
#include <SDL2/SDL.h>
#include "player.hpp"
#include "coin.hpp"
#include "item.hpp"
#include "map.hpp"
#include "background.hpp"
#include "level_editor/global.hpp"

namespace LE = level_editor;

void render()
{
    SDL_SetRenderDrawColor(rnd, 0, 0, 0, 255);
    SDL_RenderClear(rnd);

    render_background(-10, 0);
    render_items();
    render_player();
    render_coins();
    render_background(1, 10);
    render_coin_twinkles();
    render_item_names();

    if(show_debug_grid) {
        render_map();
        render_item_hitboxes();
        render_player_hitbox();
    }

    if(LE::active)
        LE::render();

    SDL_RenderPresent(rnd);
}

