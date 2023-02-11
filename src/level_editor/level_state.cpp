#include "state.hpp"
#include "../player.hpp"
#include "../level.hpp"

namespace LE = level_editor;

bool LE::restored_initial_level_state = false;
LE::StateCache LE::current_state;


void LE::restore_initial_level_state()
{
    restored_initial_level_state = true;

    cache_level_state();

    reinit_level();

}

void LE::restore_current_level_state()
{
    restored_initial_level_state = false;

    restore_state();
}


void LE::cache_level_state()
{
    Level& level = *current_level;

    current_state.player_pos = player.pos;

    current_state.collected_items.clear();
    for(auto const& item : level.entity_data.items)
        current_state
            .collected_items.push_back(item.collected);
}

void LE::reinit_level()
{
    Level& level = *current_level;

    player.pos.x = level.entity_data.player_pos.x;
    player.pos.y = level.entity_data.player_pos.y;

    for(auto& item : level.entity_data.items)
        item.collected = false;
}

void LE::restore_state()
{
    player.pos = current_state.player_pos;

    auto& items = current_level->entity_data.items;
    auto& data = current_state.collected_items;
    for(size_t i = 0; i < items.size(); ++i)
        items[i].collected = data[i];
}
