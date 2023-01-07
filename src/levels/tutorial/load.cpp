#include "levels/tutorial.hpp"
#include "level.hpp"
#include "player.hpp"
#include "camera.hpp"


/* Loads graphics (backgrounds)
 * Positions player
 * Positions camera (instant)
 * Sets current_level
 */
void tutorial::load()
{
    current_level = &level;

    player.pos.x = block_size.x * 4 * 2;
    player.pos.y = block_size.y * 4 * 17 - player.size.y;

    resize_camera();
    auto cam_pos = get_camera_target();
    camera.x = cam_pos.x;
    camera.y = cam_pos.y;

    load_backgrounds(&level);
}
