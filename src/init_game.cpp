#include "global.hpp"
#include "player.hpp"
#include "map.hpp"
#include "camera.hpp"
#include "level.hpp"

Player player;
SDL_Rect camera {0, 0, 1300, 900};


void init_game()
{
    init_levels();
    init_player_sprites();
    load_player_sprites();

}

