#include "item_menu.hpp"
#include "render.hpp"
#include "events.hpp"
#include "../item.hpp"
#include "../camera.hpp"
#include "../level.hpp"

namespace LE = level_editor;


void LE::show_item_menu()
{
    auto const& items = ::items();

    size_t count = items.size();
    size_t w = count > 4 ? 4 : count;
    size_t h = count / 4 + (count % 4 ? 1 : 0);

    item_menu.w = w * 128 + (w + 1) * 8;
    item_menu.h = h * 128 + (h + 1) * 8;

    item_menu.y = toolbar.y + toolbar.h + 8;
    item_menu.x = toolbar.x + toolbar.w - item_menu.w;
}

void LE::hide_item_menu()
{
    item_menu.w = 0;
    item_menu.h = 0;
}

bool LE::item_menu_visible()
{
    return item_menu.w > 0 && item_menu.h > 0;
}


void LE::click_item_menu(int x, int y)
{
    x -= 8;
    y -= 8;
    if(x < 0 || y < 0)
        return;

    auto const& items = ::items();

    size_t count = items.size();
    size_t w = count > 4 ? 4 : count;

    x /= 128 + 8;
    y /= 128 + 8;

    int index = x + y * w;

    auto itr = items.cbegin();
    for(int i = 0; i < index; i++)
        itr++;
    auto const& path = itr->first;
    auto const& item = itr->second;

    hide_item_menu();

    SDL_Point pos {camera.w / 2, camera.h / 2};
    undo_camera(pos);
    pos.x -= item.size.x / 2;
    pos.y -= item.size.y / 2;

    current_level->entity_data
        .items.push_back(ItemState{path, pos});
}

