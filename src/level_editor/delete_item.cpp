#include "item_menu.hpp"
#include "state.hpp"
#include "../level.hpp"
#include <algorithm>

namespace LE = level_editor;


void LE::delete_item(int index)
{
    auto& items = current_level->entity_data.items;
    std::swap(items[items.size() - 1], items[index]);
    items.pop_back();

    auto& cache = current_state.collected_items;
    {
        bool tmp = cache.back();
        cache.back() = cache[index];
        cache[index] = tmp;
    }
    cache.pop_back();
}
