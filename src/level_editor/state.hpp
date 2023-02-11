#ifndef INCLUDE_LE_STATE_HPP
#define INCLUDE_LE_STATE_HPP

#include <vector>
#include <SDL2/SDL_rect.h>

using std::vector;


namespace level_editor
{
    extern bool restored_initial_level_state;

    // Saves current state and resets level
    void restore_initial_level_state();
    // Restores saved level state
    void restore_current_level_state();


    void save_level();



    struct StateCache
    {
        SDL_FPoint player_pos;
        vector<bool> collected_items;
    };

    extern StateCache current_state;

    void cache_level_state();
    void reinit_level();
    void restore_state();
}

#endif // INCLUDE_LE_STATE_HPP
