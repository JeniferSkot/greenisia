#include "render.hpp"
#include "camera.hpp"
#include "map.hpp"
#include "level.hpp"
#include <SDL2/SDL.h>


void render_map()
{
    Map& map = current_level->map;
    for(int y = 0; y < map.height; y++)
    for(int x = 0; x < map.width; x++)
    {
        SDL_Rect block_area {
            x * block_size.x,
            y * block_size.y,
            block_size.x,
            block_size.y
        };
        SDL_Point next = {
            (x + 1) * block_size.x,
            (y + 1) * block_size.y
        };
        apply_camera(block_area.x, block_area.y);
        apply_camera(next);

        block_area.w = next.x - block_area.x - 1;
        block_area.h = next.y - block_area.y - 1;


        SDL_Color c = block_colors[*map.at(x, y)];

        SDL_SetRenderDrawColor(rnd, c.r, c.g, c.b, c.a);

        if(show_debug_grid)
            SDL_RenderDrawRect(rnd, &block_area);
    }
}
