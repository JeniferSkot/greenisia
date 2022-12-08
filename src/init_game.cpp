#include "global.hpp"
#include "player.hpp"
#include "map.hpp"

Player player;
Map map(10, 10);


void init_game()
{
    player.pos.x = 100;
    player.pos.y = 100;

    for(int x = 0; x < map.width; x++)
        map.at(x, 9) = B_SOLID;

}

