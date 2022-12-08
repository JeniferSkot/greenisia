#include "global.hpp"
#include <cstdint>
#include <SDL2/SDL_keyboard.h>
#include "Player.hpp"


void move_player(int progress)
{
    const uint8_t* keyboard = SDL_GetKeyboardState(nullptr);

    if(keyboard[SDL_SCANCODE_A] || keyboard[SDL_SCANCODE_LEFT])
        player.pos.x -= player.speed * progress / 1000.0f;

    if(keyboard[SDL_SCANCODE_D] || keyboard[SDL_SCANCODE_RIGHT])
        player.pos.x += player.speed * progress / 1000.0f;
}

