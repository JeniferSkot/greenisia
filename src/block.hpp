#ifndef INCLUDE_BLOCK_HPP
#define INCLUDE_BLOCK_HPP

#include <SDL2/SDL_pixels.h>

enum Block
{
    B_AIR,
    B_SOLID,
    B_DANGER,
    B_DEATH,

    B_LAST
};

const SDL_Color block_colors[B_LAST] {
    { 32,  32,  32, 255}, // B_AIR
    {  0, 255, 255, 255}, // B_SOLID
    {255, 255,   0, 255}, // B_DANGER
    {255,   0,   0, 255}, // B_DEATH
};


bool is_solid(Block);

#endif // INCLUDE_BLOCK_HPP
