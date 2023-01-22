#include "level_editor.hpp"
#include "level.hpp"
#include "render.hpp"
#include "camera.hpp"
#include "textures.hpp"
#include <SDL2/SDL_events.h>

namespace LE = level_editor;


void LE::render()
{
    render_border();
    render_menu_backgrounds();
    render_brush_menu();
    render_level_select();
    render_toolbar();
}

void LE::render_border()
{
    auto& map = current_level->map;

    int width = map.width * block_size.x * zoom;
    int height = map.height * block_size.y * zoom;

    SDL_Point edge {
        map_edge_markers.x * block_size.x,
        map_edge_markers.y * block_size.y
    };

    SDL_Rect top_border {0, -3, width, 3};
    SDL_Rect left_border {-3, 0, 3, height};
    SDL_Rect right_border {edge.x, 0, 3, edge.y * zoom};
    SDL_Rect bottom_border {0, edge.y, edge.x * zoom, 3};
    apply_camera(top_border.x, top_border.y);
    apply_camera(left_border.x, left_border.y);
    apply_camera(right_border.x, right_border.y);
    apply_camera(bottom_border.x, bottom_border.y);

    SDL_SetRenderDrawColor(rnd, 255, 255, 0, 255);
    SDL_RenderFillRect(rnd, &top_border);
    SDL_RenderFillRect(rnd, &left_border);
    SDL_RenderFillRect(rnd, &right_border);
    SDL_RenderFillRect(rnd, &bottom_border);
}


void LE::render_menu_backgrounds()
{
    SDL_Color bg {0, 128, 255, 127};
    SDL_SetRenderDrawColor(rnd, bg.r, bg.g, bg.b, bg.a);

    SDL_SetRenderDrawBlendMode(rnd, SDL_BLENDMODE_BLEND);
    SDL_RenderFillRect(rnd, &brush_menu);
    SDL_RenderFillRect(rnd, &toolbar);
    SDL_RenderFillRect(rnd, &level_select);
    SDL_SetRenderDrawBlendMode(rnd, SDL_BLENDMODE_NONE);
}


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


void LE::render_level_select()
{
    SDL_Rect dest {
        level_select.x, level_select.y,
        48, 48
    };
    SDL_Rect src { 0, 0, 32, 32 };

    auto texture_path = TOOLBAR_TEXTURE;
    if(!is_texture_loaded(texture_path))
        load_texture(texture_path);
    auto texture = get_texture(texture_path);

    SDL_RenderCopy(rnd, texture, &src, &dest);
}


void LE::render_toolbar()
{
    int line = 2;

    SDL_Rect dest {
        toolbar.x, toolbar.y,
        48 * line, 48
    };
    SDL_Rect src { 32, 0, 32 * line, 32 };

    auto texture_path = TOOLBAR_TEXTURE;
    if(!is_texture_loaded(texture_path))
        load_texture(texture_path);
    auto texture = get_texture(texture_path);

    //SDL_RenderCopy(rnd, texture, &src, &dest);
}

