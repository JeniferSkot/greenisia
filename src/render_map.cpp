#include "render.hpp"
#include "camera.hpp"
#include "map.hpp"
#include "level.hpp"
#include <SDL2/SDL.h>
#include <algorithm>

using std::min;
using std::max;


void render_map()
{
    Map& map = current_level->map;

    SDL_Point edge1 {0, 0};
    SDL_Point edge2 {camera.w, camera.h};
    undo_camera(edge1);
    undo_camera(edge2);

    // Render only on-screen squares
    int left = edge1.x / block_size.x;
    int top = edge1.y / block_size.y;
    int right = edge2.x / block_size.x;
    int bottom = edge2.y / block_size.y;

    left = max(0, left);
    top = max(0, top);
    bottom = min(bottom, map.height - 1);
    right = min(right, map.width - 1);

    for(int y = top; y <= bottom; y++)
    for(int x = left; x <= right; x++)
    {
        Block tile = *map.at(x, y);
        if(tile == B_AIR && zoom < 0.5)
            continue;
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

        SDL_RenderDrawRect(rnd, &block_area);
    }
}
