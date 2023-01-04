#ifndef INCLUDE_KEYBOARD_HPP
#define INCLUDE_KEYBOARD_HPP

#include <cstdint>
#include <SDL2/SDL_keyboard.h>


const uint8_t keys_up[] {
#ifdef USE_ESDF
    SDL_SCANCODE_E,
#else
    SDL_SCANCODE_W,
#endif
    SDL_SCANCODE_UP
};

const uint8_t keys_left[] {
#ifdef USE_ESDF
    SDL_SCANCODE_S,
#else
    SDL_SCANCODE_A,
#endif
    SDL_SCANCODE_LEFT
};

const uint8_t keys_down[] {
#ifdef USE_ESDF
    SDL_SCANCODE_D,
#else
    SDL_SCANCODE_S,
#endif
    SDL_SCANCODE_DOWN
};

const uint8_t keys_right[] {
#ifdef USE_ESDF
    SDL_SCANCODE_F,
#else
    SDL_SCANCODE_D,
#endif
    SDL_SCANCODE_RIGHT
};


SDL_Point keyboard_movement_input(); // range [-1, 1]

#endif // INCLUDE_KEYBOARD_HPP
