#include "level_editor.hpp"
#include "block.hpp"
#include "camera.hpp"
#include <SDL2/SDL_mouse.h>
#include <iostream>

namespace LE = level_editor;
using std::cout;
using std::endl;

Block LE::brushes[2] = {B_SOLID, B_AIR};
SDL_Rect LE::brush_menu { 8, 8, 0, 0 };
SDL_Rect LE::toolbar { 0, 8, 96, 48 };
SDL_Rect LE::level_select { 8, 0, 48, 48 };


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


void LE::position_menus()
{
    /* Brushes */
    int count = B_LAST;
    int rows = count / 10 + 1;
    int cols = std::min(10, count);

    brush_menu.w = (8 + 48) * cols + 8;
    brush_menu.h = (8 + 48) * rows + 8;


    /* Tools */
    toolbar.x = camera.w - toolbar.w - 8;

    /* Level Select */
    level_select.y = camera.h - level_select.h - 8;
}


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
}

void LE::pick_brush(int x, int y, int brush_index)
{
    auto& brush = brushes[brush_index];

    int count = B_LAST;
    int rows = count / 10 + 1;
    int cols = std::min(10, count);

    x -= 4; y -= 4;
    if(x < 0 || y < 0)
        return;

    x = x / (48 + 8);
    y = y / (48 + 8);
    if(x > cols || y > rows)
        return;

    int choice = y * cols + x;
    if(choice < B_LAST)
        brush = static_cast<Block>(choice);
}

void LE::click_level_select(int x, int)
{
    if(x <= 48)
        save_level();
}


void LE::click_toolbar(int x, int)
{
    switch(x / 48) {
    case 0: // Create
        
        break;

    case 1: // Move
        
        break;

    default:
        break;
    }
}
