#include "render.hpp"
#include "../render.hpp"
#include "../item.hpp"
#include "../textures.hpp"
#include <algorithm>

namespace LE = level_editor;
using std::min;
using std::max;


void LE::render_item_menu()
{
    auto const& items = ::items();

    size_t count = items.size();
//    size_t w = count > 4 ? 4 : count;
//    size_t h = count / 4 + (count % 4 ? 1 : 0);

    auto itr = items.cbegin();
    int index = 0;
    while(itr != items.cend()) {
        size_t x = index % 4;
        size_t y = index / 4;
        auto const& size = itr->second.size;

        SDL_Rect dest {
            item_menu.x + 8 + x * (128 + 8),
            item_menu.y + 8 + y * (128 + 8),
            min(size.x, 128),
            min(size.y, 128)
        };

        if(size.x > size.y) {
            dest.h = dest.w * size.y / size.x;
        } else if (size.y > size.x) {
            dest.w = dest.h * size.x / size.y;
        }

        dest.x += (128 - dest.w) / 2;
        dest.y += (128 - dest.h) / 2;

        auto texture = get_texture(itr->second.sprite);
        SDL_RenderCopy(rnd, texture, nullptr, &dest);

        itr++; index++;
    }

}

