#include "camera.hpp"
#include "player.hpp"
#include "level.hpp"
#include <cmath>

static SDL_Point get_player_center();
static float get_nearest_floor();


void move_camera([[maybe_unused]]int progress)
{
    auto target_pos = get_camera_target();

    const float base_speed = 0.004;

    float speed = 1 - pow(1 - base_speed, progress);
    float delay = 1 - speed;
    camera.x = (camera.x * delay + target_pos.x * speed);
    camera.y = (camera.y * delay + target_pos.y * speed);

    
    SDL_FPoint limits {
        target_camera_size.x * (1 - zoom) / 2,
        target_camera_size.y * (1 - zoom) / 2
    };

    if(camera.x < limits.x)
        camera.x = limits.x;

    if(camera.y < limits.y)
        camera.y = limits.y;
}


SDL_Point get_camera_target()
{
    SDL_Point player_center = get_player_center();
    float nearest_floor = get_nearest_floor();

    SDL_Point target_pos {
        player_center.x,
        static_cast<int>
            ((player_center.y + nearest_floor) / 2)
    };

    float player_dx = player.pos.x - player.old_pos.x;
    if(player_dx > 0) { // right
        target_pos.x += camera.w / 2; 
    } else if(player_dx < 0) { // left
        target_pos.x -= camera.w / 2;
    }

    target_pos.x = target_pos.x - camera.w / 2;
    target_pos.y = target_pos.y - 3 * camera.h / 4;

    return target_pos;
}


SDL_Point get_player_center()
{
    auto const& pos = player.pos;
    auto const& size = player.size;

    return {
        static_cast<int>(pos.x + size.x / 2),
        static_cast<int>(pos.y + size.y / 2)
    };
}


float get_nearest_floor()
{
    Map& map = current_level->map;
    auto& bs = block_size;
    int x1 = player.pos.x / bs.x;
    int x2 = (player.pos.x + player.size.x) / bs.x;
    float y1 = (player.pos.y + player.size.y) / bs.y;
    float y2 = y1 + player.size.y * 2 / bs.y;

    for(int y = y1; y <= y2; y++)
    for(int x = x1; x <= x2; x++) {
        Block* block = map.at(x, y);
        if(block && *block != B_AIR)
            return y * bs.y;
    }

    return y2 * bs.y;
}

