#include "camera.hpp"
#include "player.hpp"


void move_camera(int progress)
{
    camera.x = player.pos.x + player.size.x / 2
                - camera.w / 2;
    camera.y = player.pos.y + player.size.y / 2
                - camera.h / 2;
}
