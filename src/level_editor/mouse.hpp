#ifndef INCLUDE_LE_MOUSE_HPP
#define INCLUDE_LE_MOUSE_HPP

#include <SDL2/SDL_rect.h>

namespace level_editor
{
    enum MouseMode {
        MM_NONE,
        MM_MOVING,
        MM_BRUSH1,
        MM_BRUSH2,
        MM_RESIZING,
        MM_DRAGGING_PLAYER,
        MM_DRAGGING_ITEM,
    };

    extern MouseMode mmode;
    extern int target_item;

    // In map coordinates
    extern SDL_FPoint mouse;
    extern SDL_FPoint last_mouse;
    extern SDL_FPoint last_target;

    // Used in camera dragging
    extern SDL_Point last_screen_mouse;

    
}

#endif // INCLUDE_LE_MOUSE_HPP
