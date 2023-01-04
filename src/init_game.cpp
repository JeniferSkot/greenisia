#include "global.hpp"
#include "render.hpp"
#include "player.hpp"
#include "map.hpp"
#include "camera.hpp"
#include "level.hpp"
#include <iostream>

using std::cout;
using std::endl;


Player player;
SDL_Rect camera;
float zoom = 1.0f;


void init_game()
{
    init_levels();
    init_player_sprites();
    load_player_sprites();

#ifdef LEVEL_EDITOR
    cout << endl;
    cout << "*****************************" << endl;
    cout << "Built with LEVEL_EDITOR flag" << endl;
    cout << "Press L to edit current level" << endl;
    cout << "*****************************" << endl;
    cout << endl;
#endif
}

