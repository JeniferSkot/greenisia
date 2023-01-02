#include "camera.hpp"
#include "player.hpp"
#include "global.hpp"


void move_camera(int progress)
{
    SDL_GetRendererOutputSize(rnd, &camera.w, &camera.h);

    camera.x = player.pos.x + player.size.x / 2
                - camera.w / 2;
    camera.y = player.pos.y - camera.h / 2;

    if(camera.x < 0)
        camera.x = 0;

    if(camera.y < 0)
        camera.y = 0;
}
