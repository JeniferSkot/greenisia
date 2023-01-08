#ifndef INCLUDE_BLOCK_HPP
#define INCLUDE_BLOCK_HPP

#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_rect.h>

enum Block : uint8_t
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

const SDL_Point block_size {24, 24};

bool is_solid(Block);

#endif // INCLUDE_BLOCK_HPP
