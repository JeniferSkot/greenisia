#include "global.hpp"
#include <cstdint>
#include <SDL2/SDL_keyboard.h>
#include "player.hpp"
#include "camera.hpp"


void tick(int progress)
{
    if(progress > 30)
        progress = 30;
    move_player(progress);
    move_camera(progress);
}

