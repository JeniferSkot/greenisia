#include "utils.hpp"
#include "render.hpp"
#include "../level.hpp"
#include "../camera.hpp"
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

