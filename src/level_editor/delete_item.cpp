#include "item_menu.hpp"
#include "state.hpp"
#include "../level.hpp"
#include <algorithm>

namespace LE = level_editor;


void LE::delete_item(int index)
{
    auto& items = current_level->entity_data.items;
    std::swap(items.back(), items.at(index));
    items.pop_back();

    auto& cache = current_state.collected_items;
    std::swap(cache.back(), cache.at(index));
    cache.pop_back();
}
