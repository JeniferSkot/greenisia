#include "global.hpp"
#include <cstdint>
#include <SDL2/SDL_keyboard.h>
#include "Player.hpp"


void tick(int progress)
{
    move_player(progress);
}

