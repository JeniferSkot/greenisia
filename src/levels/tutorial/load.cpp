#include "levels/tutorial.hpp"
#include "global.hpp"
#include "level.hpp"
#include "player.hpp"
#include "camera.hpp"


void tutorial::load()
{
    current_level = &level;

    player.pos.x = block_size.x * 2;
    player.pos.y = block_size.y * 17 - player.size.y;

    auto cam_pos = get_camera_target();
    camera.x = cam_pos.x;
    camera.y = cam_pos.y;

    load_backgrounds(&level);
}
