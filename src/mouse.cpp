#include "global.hpp"
#include "camera.hpp"
#include "coin.hpp"
#include <SDL2/SDL_events.h>
#include <iostream>

using std::cout;
using std::endl;

bool spawning = false;


void mousedown(SDL_MouseButtonEvent&)
{
    spawning = true;
}

void mousemotion(SDL_MouseMotionEvent& ev)
{
    if(!spawning)
        return;

    SDL_Point pos {ev.x, ev.y};
    undo_camera(pos);

    spawn_coins(pos.x, pos.y, 50);
}

void mouseup(SDL_MouseButtonEvent&)
{
    spawning = false;
}
