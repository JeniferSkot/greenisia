#ifndef INCLUDE_ITEM_SELECT_HPP
#define INCLUDE_ITEM_SELECT_HPP

namespace level_editor
{
    void show_item_menu();
    void hide_item_menu();
    bool item_menu_visible();

    void show_item_story_menu();
    void hide_item_story_menu();
    bool item_story_menu_visible();

    void delete_item(int index);
}

#endif // INCLUDE_ITEM_SELECT_HPP
