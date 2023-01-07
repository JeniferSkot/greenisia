#include "level_editor.hpp"
#include "block.hpp"
#include "camera.hpp"
#include <SDL2/SDL_mouse.h>
#include <iostream>

namespace LE = level_editor;
using std::cout;
using std::endl;

Block LE::brushes[2] = {B_SOLID, B_AIR};
SDL_Rect LE::brush_menu {0, 0, 0, 0};
SDL_Rect LE::toolbar {0, 0, 0, 0};


bool LE::in_menu(int x, int y)
{
    SDL_Point point {x, y};
    SDL_Rect* menus[] {
        &brush_menu,
        &toolbar
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

    if(SDL_PointInRect(&point, &toolbar)) {
        
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

