#ifndef INCLUDE_LE_EVENTS_HPP
#define INCLUDE_LE_EVENTS_HPP

struct SDL_MouseButtonEvent;

namespace level_editor
{
    void on_menu_click(int x, int y, int button);
    void item_mousedown(SDL_MouseButtonEvent&);

    void pick_brush(int x, int y, int brush_index);
    void click_level_select(int x, int y);
    void click_toolbar(int x, int y);
    void click_item_menu(int x, int y);
    void click_item_story_menu(int x, int y);
}

#endif // INCLUDE_LE_EVENTS_HPP
