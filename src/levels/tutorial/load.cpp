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
    // level.entity_data.player_pos.x = 16 * 4 * 2;
    // level.entity_data.player_pos.y = 16 * 4 * 17 - player.size.y;

    current_level = &level;

    player.pos.x = level.entity_data.player_pos.x;
    player.pos.y = level.entity_data.player_pos.y;

    resize_camera();
    auto cam_pos = get_camera_target();
    camera.x = cam_pos.x;
    camera.y = cam_pos.y;

    load_backgrounds(&level);
}
