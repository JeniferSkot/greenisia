#include "global.hpp"
#include "player.hpp"
#include "camera.hpp"
#include "textures.hpp"

#include <SDL2/SDL.h>


void render_player()
{
    SDL_Rect player_area {
        player.pos.x - camera.x,
        player.pos.y - camera.y,
        player.size.x,
        player.size.y
    };

    SDL_Point offset, tex_size;
    auto texture = get_player_sprite(&offset, &tex_size);
    SDL_Rect sprite_area {
        player_area.x + offset.x,
        player_area.y + offset.y,
        tex_size.x,
        tex_size.y
    };

    SDL_RenderCopy(rnd, texture, nullptr, &sprite_area);

    if(SHOW_DEBUG_GRID) {
        SDL_SetRenderDrawColor(rnd, 0, 255, 0, 255);
        SDL_RenderDrawRect(rnd, &player_area);
    }
}
