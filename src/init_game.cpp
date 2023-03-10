#include "global.hpp"
#include "render.hpp"
#include "player.hpp"
#include "coin.hpp"
#include "item.hpp"
#include "story.hpp"
#include "map.hpp"
#include "camera.hpp"
#include "level.hpp"
#include "text.hpp"
#include <iostream>

using std::cout;
using std::endl;


Player player;
SDL_Rect camera;
float zoom = 1.0f;

#ifdef DEBUG_GRID
bool show_debug_grid = true;
#endif


void init_game()
{
    render_loading_screen();

    init_levels();
    init_player_sprites();
    load_player_sprites();
    load_coin_sprites();
    load_items();
    load_characters();
    load_stories();
    font();

    cout << "Game loaded!" << endl;

#ifdef QUICK_QUIT
    cout << endl;
    cout << "*****************************" << endl;
    cout << "Built with QUICK_QUIT flag" << endl;
    cout << "Press Q to close the game" << endl;
    cout << "*****************************" << endl;
#endif

#ifdef USE_ESDF
    cout << endl;
    cout << "*****************************" << endl;
    cout << "Built with USE_ESDF flag" << endl;
    cout << "Use ESDF to move instead WASD" << endl;
    cout << "*****************************" << endl;
#endif

#ifdef DEBUG_GRID
    cout << endl;
    cout << "*****************************" << endl;
    cout << "Built with DEBUG_GRID flag" << endl;
    cout << "Press G to disable debug grid" << endl;
    cout << "*****************************" << endl;
#endif

#ifdef LEVEL_EDITOR
    cout << endl;
    cout << "*****************************" << endl;
    cout << "Built with LEVEL_EDITOR flag" << endl;
    cout << "Press L or R for level editor" << endl;
    cout << "*****************************" << endl;
#endif

    cout << endl;
}

