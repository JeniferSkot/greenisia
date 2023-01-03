#include "global.hpp"
#include "camera.hpp"
#include "map.hpp"
#include "level.hpp"
#include <SDL2/SDL.h>


static const SDL_Color block_color[] {
    {  0,   0,   0, 255}, // B_AIR
    {  0,   0, 255, 255}, // B_SOLID
    {255, 255,   0, 255}, // B_DANGER
    {255,   0,   0, 255}, // B_DEATH
};


void render_map()
{
    Map& map = current_level->map;
    for(int y = 0; y < map.height; y++)
    for(int x = 0; x < map.width; x++)
    {
        SDL_Rect block_area {
            x * block_size.x - camera.x,
            y * block_size.y - camera.y,
            block_size.x,
            block_size.y
        };


        SDL_Color c = block_color[*map.at(x, y)];

        SDL_SetRenderDrawColor(rnd, c.r, c.g, c.b, c.a);

        if(SHOW_DEBUG_GRID)
            SDL_RenderDrawRect(rnd, &block_area);
    }
}
