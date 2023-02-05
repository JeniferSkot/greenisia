#include "camera.hpp"
#include "player.hpp"
#include "level.hpp"
#include <cmath>
#include <iostream>

using std::cout;
using std::endl;

static SDL_Point get_player_center();
static float get_lowest_floor(int lrange, int rrange);


void move_camera([[maybe_unused]]int progress)
{
    auto target_pos = get_camera_target();

    const float base_speed = 0.0036;

    float speed = 1 - pow(1 - base_speed, progress);
    float rest = 1 - speed;
    camera.x = (camera.x * rest + target_pos.x * speed);
    camera.y = (camera.y * rest + target_pos.y * speed);

    
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
    float player_dx = player.pos.x - player.old_pos.x;

    float lowest_floor;
    /* Find lowest floor pos.y */ {
        int lrange = 8;
        int rrange = 8;
        if(player_dx > 0) { // moving right
            lrange = - player.size.x / block_size.x;
            rrange += 42;
        } else if(player_dx < 0) { // moving left
            lrange += 42;
            rrange = - player.size.x / block_size.x;
        }

        lowest_floor = get_lowest_floor(lrange, rrange);
    }

    SDL_Point target_pos {
        player_center.x,
        static_cast<int>
            ((player_center.y + lowest_floor) / 2)
    };


    if(player_dx > 0) // right
        target_pos.x += (camera.w / zoom) / 2; 
    else if(player_dx < 0) // left
        target_pos.x -= (camera.w / zoom) / 2;
    

    target_pos.x = target_pos.x - camera.w / 2;
    target_pos.y = target_pos.y - 2 * camera.h / 3;

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


float get_lowest_floor(int lrange, int rrange)
{
    Map& map = current_level->map;
    auto const& bs = block_size;
    auto const& pos = player.pos;
    auto const& size = player.size;

    int x1 = pos.x / bs.x - lrange;
    int x2 = (pos.x + size.x) / bs.x + rrange;
    if(x1 < 0) x1 = 0;
    if(x2 >= map.width) x2 = map.width - 1;

    float y1 = (pos.y - size.y) / bs.y;
    float y2 = pos.y / bs.y + size.y * 3 / bs.y;

    for(int y = y2; y >= y1; y--)
    for(int x = x1; x <= x2; x++) {
        Block* block = map.at(x, y);
        if(block && *block != B_AIR) {
            return y * bs.y;
        }
    }

    return y2 * bs.y;
}

