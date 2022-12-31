#include "levels/tutorial.hpp"
#include "level.hpp"
#include "player.hpp"

Level tutorial::level;


void tutorial::init()
{
    Map map(25, 19);

    for(int x = 0; x < map.width / 2; x++)
        map.at(x, 9) = B_SOLID;
    for(int x = map.width / 2; x < map.width; x++)
        map.at(x, 13) = B_SOLID;
    for(int x = 0; x < map.width; x++)
        map.at(x, 18) = B_SOLID;

    map.at(5, 8) = B_SOLID;
    map.at(15, 17) = B_SOLID;


    level.map = map;
}

void tutorial::load()
{
    current_level = &level;

    player.pos.x = 100;
    player.pos.y = 100;
}
