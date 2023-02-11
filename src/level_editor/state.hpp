#ifndef INCLUDE_LE_STATE_HPP
#define INCLUDE_LE_STATE_HPP

namespace level_editor
{
    extern bool restored_initial_level_state;

    // Saves current state and resets level
    void restore_initial_level_state();
    // Restores saved level state
    void restore_current_level_state();


    void save_level();
}

#endif // INCLUDE_LE_STATE_HPP
