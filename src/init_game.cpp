#include "global.hpp"
#include "player.hpp"
#include "map.hpp"
#include "camera.hpp"
#include "level.hpp"

Player player;
SDL_Rect camera {0, 0, window_size.x, window_size.y};
float zoom = 1.0f;


void init_game()
{
    init_levels();
    init_player_sprites();
    load_player_sprites();

}

