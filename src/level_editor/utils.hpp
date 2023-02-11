#ifndef INCLUDE_LE_UTILS_HPP
#define INCLUDE_LE_UTILS_HPP

#include <SDL2/SDL_rect.h>

namespace level_editor
{
    void print_help();

    bool in_board(int x, int y);
    bool in_menu(int x, int y);

    // In map coordinates
    SDL_FPoint get_mouse_pos();
}

#endif // INCLUDE_LE_UTILS_HPP
