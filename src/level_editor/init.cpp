#include "level_editor.hpp"

namespace LE = level_editor;


void LE::init()
{
    restored_initial_level_state = false;
}

void LE::deinit()
{
    if(restored_initial_level_state)
        restore_current_level_state();
}
