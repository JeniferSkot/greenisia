#include "events.hpp"
#include "state.hpp"

namespace LE = level_editor;


void LE::click_toolbar(int x, int)
{
    switch(x / 48) {
    case 0: // Create
        
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

