#include "events.hpp"
#include "state.hpp"

namespace LE = level_editor;


void LE::click_level_select(int x, int)
{
    if(x <= 48)
        save_level();
}

