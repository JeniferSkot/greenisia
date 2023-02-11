#include "utils.hpp"
#include "render.hpp"
#include "state.hpp"
#include "../level.hpp"
#include "../camera.hpp"
#include "../player.hpp"
#include <SDL2/SDL_rect.h>

namespace LE = level_editor;


bool LE::in_menu(int x, int y)
{
    SDL_Point point {x, y};
    SDL_Rect* menus[] {
        &brush_menu,
        &toolbar,
        &level_select
    };

    for(auto menu : menus)
        if(SDL_PointInRect(&point, menu))
            return true;

    return false;
}

bool LE::in_board(int x, int y)
{
    undo_camera(x, y);
    x = x / block_size.x;
    y = y / block_size.y;
    return current_level->map.at(x, y);
}


bool LE::is_draggable(int x, int y)
{
    if(is_player(x, y))
        return true;

    if(restored_initial_level_state)
        if(is_item(x, y))
            return true;

    return false;
}

bool LE::is_player(int x, int y)
{
    undo_camera(x, y);
    SDL_Point point {x, y};


    SDL_Rect player_area {
        static_cast<int>(player.pos.x),
        static_cast<int>(player.pos.y),
        player.size.x,
        player.size.y
    };

    if(SDL_PointInRect(&point, &player_area))
        return true;

    return false;
}

bool LE::is_item(int x, int y)
{
    return get_item_entry_index(x, y) != -1;
}

int LE::get_item_entry_index(int x, int y)
{
    undo_camera(x, y);
    SDL_Point point {x, y};

    Level const& level = *current_level;
    auto const& items = level.entity_data.items;
    for(size_t i = 0; i < items.size(); ++i) {
        auto const& item = items[i];
        auto const& data = ::item(item.item);
        SDL_Rect item_area {
            item.pos.x,
            item.pos.y,
            data.size.x,
            data.size.y
        };
        if(SDL_PointInRect(&point, &item_area))
            return i;
    }

    return -1;
}
