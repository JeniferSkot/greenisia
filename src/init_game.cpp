#include "global.hpp"
#include "player.hpp"
#include "map.hpp"
#include "camera.hpp"
#include "level.hpp"

Player player;
SDL_Rect camera {0, 0, 1200, 800};


void init_game()
{
    init_levels();

}

