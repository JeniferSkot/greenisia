#include "render.hpp"
#include "../render.hpp"
#include "../story.hpp"
#include "../text.hpp"
#include <algorithm>

namespace LE = level_editor;
using std::min;
using std::max;


void LE::render_item_story_menu()
{
    auto const& stories = ::stories();

    SDL_Point pos {
        item_story_menu.x + 8,
        item_story_menu.y + 8
    };

    auto itr = stories.cbegin();
    while(itr != stories.cend()) {
        SDL_Point size;
        string key = itr->first.stem();
        auto tex = render_text_cached(key, &size);

        SDL_Rect dest {
            pos.x,
            pos.y,
            size.x,
            size.y
        };
        pos.y += size.y + 8;

        SDL_RenderCopy(rnd, tex, nullptr, &dest);
        itr++;
    }

}

