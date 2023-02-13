#ifndef INCLUDE_LE_EVENTS_HPP
#define INCLUDE_LE_EVENTS_HPP

namespace level_editor
{
    void on_menu_click(int x, int y, int button);

    void pick_brush(int x, int y, int brush_index);
    void click_level_select(int x, int y);
    void click_toolbar(int x, int y);
    void click_item_menu(int x, int y);
}

#endif // INCLUDE_LE_EVENTS_HPP
