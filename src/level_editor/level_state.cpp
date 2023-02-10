#include "level_editor.hpp"

namespace LE = level_editor;


bool LE::restored_initial_level_state = false;


// Saves current state and resets level
void LE::restore_inital_level_state()
{
    restored_initial_level_state = true;
    // TODO implement
}

// Restores saved state
void LE::restore_current_level_state()
{
    restored_initial_level_state = false;
    // TODO implement
}
