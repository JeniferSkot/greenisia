#include "events.hpp"
#include "state.hpp"
#include "item_menu.hpp"
#include <iostream>

using std::cout;
using std::endl;
namespace LE = level_editor;


void LE::click_toolbar(int x, int)
{
    switch(x / 48) {
    case 0: // Create
        if(!restored_initial_level_state) {
            cout << "Please restore initial state"
                    " before adding items." << endl;
        } else {
            if(item_menu_visible())
                hide_item_menu();
            else
                show_item_menu();
        }
        break;

    case 1: // Move
        if(restored_initial_level_state)
            restore_current_level_state();
        else
            restore_initial_level_state();
        break;

    default:
        break;
    }
}

