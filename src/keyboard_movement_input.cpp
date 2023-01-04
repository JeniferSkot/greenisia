#include "keyboard.hpp"


SDL_Point keyboard_movement_input() // [-1, 1]
{
    const uint8_t* keyboard = SDL_GetKeyboardState(nullptr);
    SDL_Point input {0, 0};

    for(auto key : keys_up)
        if(keyboard[key]) {
            input.y--;
            break;
        }

    for(auto key : keys_left)
        if(keyboard[key]) {
            input.x--;
            break;
        }

    for(auto key : keys_down)
        if(keyboard[key]) {
            input.y++;
            break;
        }

    for(auto key : keys_right)
        if(keyboard[key]) {
            input.x++;
            break;
        }

    return input;
}

