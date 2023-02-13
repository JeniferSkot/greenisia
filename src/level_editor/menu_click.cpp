#include "render.hpp"
#include "events.hpp"
#include <SDL2/SDL_mouse.h>

namespace LE = level_editor;


void LE::on_menu_click(int x, int y, int button)
{
    SDL_Point point {x, y};

    if(SDL_PointInRect(&point, &brush_menu)) {
        x -= brush_menu.x;
        y -= brush_menu.y;
        if(button == SDL_BUTTON_LEFT)
            pick_brush(x, y, 0);
        if(button == SDL_BUTTON_RIGHT)
            pick_brush(x, y, 1);
        return;
    }

    if(SDL_PointInRect(&point, &level_select)) {
        x -= level_select.x;
        y -= level_select.y;
        click_level_select(x, y);
        return;
    }

    if(SDL_PointInRect(&point, &toolbar)) {
        x -= toolbar.x;
        y -= toolbar.y;
        click_toolbar(x, y);
        return;
    }

    if(SDL_PointInRect(&point, &item_menu)) {
        x -= item_menu.x;
        y -= item_menu.y;
        click_item_menu(x, y);
        return;
    }
}

