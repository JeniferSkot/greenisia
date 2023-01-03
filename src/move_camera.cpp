#include "camera.hpp"
#include "player.hpp"
#include "level.hpp"
#include "global.hpp"

static SDL_Point get_player_center();
static SDL_Point get_nearest_floor();


void move_camera([[maybe_unused]]int progress)
{
    SDL_Point player_center = get_player_center();
    SDL_Point nearest_floor = get_nearest_floor();

    SDL_Point target_pos {
        (player_center.x + nearest_floor.x) / 2,
        (player_center.y + nearest_floor.y) / 2
    };

    camera.x = target_pos.x - camera.w / 2;
    camera.y = target_pos.y - 2 * camera.h / 3;


    if(camera.x < 0)
        camera.x = 0;

    if(camera.y < 0)
        camera.y = 0;
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


SDL_Point get_nearest_floor()
{
    Map& map = current_level->map;
    auto& bs = block_size;
    int x1 = player.pos.x / bs.x;
    int x2 = (player.pos.x + player.size.x) / bs.x;
    int y1 = (player.pos.y + player.size.y) / bs.y;
    int y2 = y1 + player.size.y * 1.5 / bs.y;

    float out_x = x1;
    float out_y = y1;

    for(int y = y1; y <= y2; y++) {
        int solid_count= 0;
        float sum = 0;

        for(int x = x1; x <= x2; x++) {
            Block* block = map.at(x, y);
            if(block && *block != B_AIR) {
                solid_count++;
                sum += x;
            }
        }

        if(solid_count > 0) {
            out_y = y;
            out_x = sum / solid_count;
        }
    }

    return {
        static_cast<int>(out_x * bs.x),
        static_cast<int>(out_y * bs.y)
    };
}
