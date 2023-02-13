#include "item_menu.hpp"
#include "render.hpp"
#include "../item.hpp"

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

