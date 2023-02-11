#ifndef INCLUDE_LE_UTILS_HPP
#define INCLUDE_LE_UTILS_HPP

#include <SDL2/SDL_rect.h>

namespace level_editor
{
    void print_help();

    bool in_board(int x, int y);
    bool in_menu(int x, int y);

    bool is_draggable(int x, int y);
    bool is_player(int x, int y);
    bool is_item(int x, int y);
    int get_item_entry_index(int x, int y);


    // In map coordinates
    SDL_FPoint get_mouse_pos();
}

#endif // INCLUDE_LE_UTILS_HPP
