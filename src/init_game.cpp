#include "global.hpp"
#include "player.hpp"
#include "map.hpp"
#include "camera.hpp"

Player player;
Map map(25, 19);

SDL_Rect camera {0, 0, 800, 600};

void init_game()
{
    player.pos.x = 100;
    player.pos.y = 100;

    for(int x = 0; x < map.width / 2; x++)
        map.at(x, 9) = B_SOLID;
    for(int x = map.width / 2; x < map.width; x++)
        map.at(x, 13) = B_SOLID;
    for(int x = 0; x < map.width; x++)
        map.at(x, 18) = B_SOLID;

    map.at(5, 8) = B_SOLID;
    map.at(15, 17) = B_SOLID;
}

