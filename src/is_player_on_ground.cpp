#include "global.hpp"
#include "player.hpp"
#include "level.hpp"


bool is_player_on_ground()
{
    Map const& map = current_level->map;
    auto const& bsize = block_size;
    auto const& pos = player.pos;
    auto const& size = player.size;

    int x1 = pos.x / bsize.x;
    int x2 = (pos.x + size.x) / bsize.x;
    int y = (pos.y + size.y) / bsize.y;

    for(int x = x1; x <= x2; x++) {
        Block const* block = map.at(x, y);
        if(block && is_solid(*block))
            return true;
    }

    return false;
}
