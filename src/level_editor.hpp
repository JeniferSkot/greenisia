#ifndef INCLUDE_LEVEL_EDITOR_HPP
#define INCLUDE_LEVEL_EDITOR_HPP

#include "block.hpp"
#include <SDL2/SDL_rect.h>

struct SDL_MouseButtonEvent;
struct SDL_MouseWheelEvent;


namespace level_editor
{
#ifdef LEVEL_EDITOR
    extern bool active;
#else
    const bool active = false;
#endif

    extern Block brushes[2];
    const auto BRUSH_MENU_TEXTURE
        = "assets/menu/brushes_menu.png";

    const auto TOOLBAR_TEXTURE
        = "assets/menu/level_edit_menu.png";

    void print_help();

    void on_mousedown(SDL_MouseButtonEvent&);
    void on_mouseup(SDL_MouseButtonEvent&);
    void on_mousewheel(SDL_MouseWheelEvent&);

    void tick(int progress);
    void render();
    void render_menu_backgrounds();
    void render_brush_menu();
    void render_toolbar();
    void render_border();

    /* MENU */
    extern SDL_Rect brush_menu;
    extern SDL_Rect toolbar;

    void position_menus();

    bool in_menu(int x, int y);
    void on_menu_click(int x, int y, int button);
    void pick_brush(int x, int y, int brush_index);
    void click_toolbar(int x, int y);

    void save_level();
    void save_map();
}

#endif // INCLUDE_LEVEL_EDITOR_HPP
