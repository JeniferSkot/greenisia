#include "item.hpp"
#include "level.hpp"
#include "player.hpp"
#include "story.hpp"


static bool has_player_collision(SDL_Rect const&);

void collect_items()
{
    auto& items = current_level->entity_data.items;
    for(auto& state : items) {
        if(state.collected)
            continue;

        auto const& item = ::item(state.item);

        SDL_Rect area {
            state.pos.x,
            state.pos.y,
            item.size.x,
            item.size.y
        };

        if(!has_player_collision(area))
            continue;

        state.collected = true;
        auto const& cue = state.story_cue;
        if(!cue.empty())
            start_story(cue);
    }

}

bool has_player_collision(SDL_Rect const& pos)
{
    const int range = block_size.x;
    if(pos.x < player.pos.x + player.size.x + range)
    if(pos.x + pos.w > player.pos.x - range)
    if(pos.y < player.pos.y + player.size.y + range*3)
    if(pos.y + pos.h > player.pos.y - range)
        return true;
    return false;
}

