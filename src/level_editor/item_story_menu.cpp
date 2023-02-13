#include "item_menu.hpp"
#include "render.hpp"
#include "events.hpp"
#include "mouse.hpp"
#include "../story.hpp"
#include "../text.hpp"
#include "../camera.hpp"
#include "../level.hpp"
#include <algorithm>

namespace LE = level_editor;
using std::max;



void LE::show_item_story_menu()
{
    auto const& stories = ::stories();
    auto& area = item_story_menu;

    SDL_Point size {0, 0};

    for(auto const& pair : stories) {
        string key = pair.first.stem();
        SDL_Point tsize;
        render_text_cached(key, &tsize);
        size.y += tsize.y + 8;
        size.x = max(size.x, tsize.x);
    }

    area.w = size.x + 16;
    area.h = size.y + 16;
    area.x = toolbar.x + toolbar.w - area.w;
    area.y = toolbar.y + toolbar.h + 8;

    if(area.x < 0)
        area.x = 0;
    if(area.h + area.y > camera.h - 8)
        area.h = camera.h - area.y - 8;
}

void LE::hide_item_story_menu()
{
    item_story_menu.w = 0;
    item_story_menu.h = 0;
}

bool LE::item_story_menu_visible()
{
    return item_story_menu.w > 0
        && item_story_menu.h > 0;
}


void LE::click_item_story_menu(int x, int y)
{
    x -= 8;
    y -= 8;
    if(x < 0 || y < 0)
        return;

    hide_item_story_menu();

    auto const& stories = ::stories();

    int h = 8;
    for(auto const& pair : stories) {
        SDL_Point size;
        string key = pair.first.stem();
        render_text_cached(key, &size);
        h += size.y + 8;
        if(y < h) {
            auto& data = current_level->entity_data;
            auto& item = data.items[target_item];
            item.story_cue = pair.first;
            return;
        }
    }
}
