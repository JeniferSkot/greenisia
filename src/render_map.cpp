#include "global.hpp"
#include <SDL2/SDL.h>
#include "map.hpp"

static const SDL_Color block_color[] {
    {  0,   0,   0, 255}, // B_AIR
    {  0,   0, 255, 255}, // B_SOLID
    {255, 255,   0, 255}, // B_DANGER
    {255,   0,   0, 255}, // B_DEATH
};


void render_map()
{
    const SDL_Point block_size {32, 32};

    for(int y = 0; y < map.height; y++)
    for(int x = 0; x < map.width; x++)
    {
        SDL_Rect block_area {
            x * block_size.x,
            y * block_size.y,
            block_size.x,
            block_size.y
        };


        SDL_Color c = block_color[map.at(x, y)];

        SDL_SetRenderDrawColor(rnd, c.r, c.g, c.b, c.a);

        SDL_RenderFillRect(rnd, &block_area);
    }
}
