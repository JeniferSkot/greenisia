#include "events.hpp"
#include "../block.hpp"

namespace LE = level_editor;


void LE::click_toolbar(int x, int)
{
    switch(x / 48) {
    case 0: // Create
        
        break;

    case 1: // Move
        //restore_scene();
        break;

    default:
        break;
    }
}

