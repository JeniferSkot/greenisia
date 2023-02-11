#include "render.hpp"
#include "config.hpp"
#include "map.hpp"
#include "../render.hpp"
#include "../textures.hpp"

namespace LE = level_editor;


void LE::render_brush_menu()
{
    for(int i = 0; i < B_LAST; i++) {
        auto c = block_colors[i];
        int row = i / 10;
        int col = i % 10;
        SDL_Rect brush {
            brush_menu.x + 8 + (8 + 48) * col,
            brush_menu.y + 8 + (8 + 48) * row,
            48, 48
        };

        SDL_SetRenderDrawColor(rnd, c.r, c.g, c.b, c.a);
        SDL_RenderFillRect(rnd, &brush);

        int brush_c = sizeof brushes / sizeof brushes[0];
        for(int b = 0; b < brush_c; b++) {
            if(i != brushes[b])
                continue;

            auto texture_path = BRUSH_MENU_TEXTURE;
            if(!is_texture_loaded(texture_path))
                load_texture(texture_path);
            auto texture = get_texture(texture_path);

            SDL_Rect src {
                b * 48,
                0,
                48,
                48
            };
            SDL_RenderCopy(rnd, texture, &src, &brush);
        }
    }
}

