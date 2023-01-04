#include "global.hpp"
#include "player.hpp"
#include "camera.hpp"
#include "textures.hpp"

#include <SDL2/SDL.h>


void render_player()
{
    SDL_Point offset, tex_size;
    auto texture = get_player_sprite(&offset, &tex_size);
    SDL_Rect sprite_area {
        static_cast<int>(player.pos.x) + offset.x,
        static_cast<int>(player.pos.y) + offset.y,
        tex_size.x,
        tex_size.y
    };
    apply_camera(sprite_area);

    float delta_x = player.pos.x - player.old_pos.x;
    if(delta_x < 0)
        SDL_RenderCopyEx(rnd, texture,
                         nullptr, &sprite_area,
                         0, nullptr,
                         SDL_FLIP_HORIZONTAL);
    else
        SDL_RenderCopy(rnd, texture,
                       nullptr, &sprite_area);
    

    if(SHOW_DEBUG_GRID) { // Player hitbox
        SDL_Rect player_area {
            static_cast<int>(player.pos.x),
            static_cast<int>(player.pos.y),
            player.size.x,
            player.size.y
        };
        apply_camera(player_area);

        SDL_SetRenderDrawColor(rnd, 0, 255, 0, 255);
        SDL_RenderDrawRect(rnd, &player_area);
    }
}
