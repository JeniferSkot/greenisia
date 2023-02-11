#ifndef INCLUDE_LE_TICK_HPP
#define INCLUDE_LE_TICK_HPP

#include <SDL2/SDL_rect.h>

namespace level_editor
{
    /* Mouse state dependent */
    void tick_dragging(int);
    void tick_painting(int, int brush);
    void tick_resizing(int);
    void tick_idle(int);

    /* Miscellaneous */
    void tick_keyboard_movement(int);
    void tick_fix_edge_markers(int);
}

#endif // INCLUDE_LE_TICK_HPP
