#include "level_editor.hpp"
#include "camera.hpp"
#include "level.hpp"
#include <SDL2/SDL_events.h>
#include <iostream>
#include "keyboard.hpp"
#include "render.hpp"

namespace LE = level_editor;
using std::cout;
using std::endl;


enum MouseMode {
    MM_NONE,
    MM_MOVING,
    MM_PLACING,
    MM_CLEARING
};

static MouseMode mode = MM_NONE;
static void apply_action(int x, int y);
static SDL_Point mouse {0, 0};


void LE::print_help()
{
    cout << endl;
    cout << "====== Level Editor help ======" << endl;
    cout << "Press L to disable level editor" << endl;
    cout << endl;
    cout << "Menu Left Click: action" << endl;
    cout << endl;
    cout << "Left click/drag: place block" << endl;
    cout << "Right click/drag: clear block" << endl;
    cout << endl;
    cout << "Middle click+drag: move camera" << endl;
    cout << "Movement keys: move camera" << endl;
    cout << "===============================" << endl;
    cout << endl;
}

void LE::on_mousedown(SDL_MouseButtonEvent& ev)
{
    switch(ev.button) {
        case SDL_BUTTON_LEFT:
            mode = MM_PLACING;
            break;
        case SDL_BUTTON_RIGHT:
            mode = MM_CLEARING;
            break;
        case SDL_BUTTON_MIDDLE:
            mode = MM_MOVING;
            break;
        default:
            return;
    }
    mouse = {ev.x, ev.y};

    if(mode != MM_MOVING)
        apply_action(ev.x, ev.y);
}

void LE::on_mouseup(SDL_MouseButtonEvent&)
{
    mode = MM_NONE;
}

void LE::tick(int)
{
    SDL_Point mouse2;
    SDL_GetMouseState(&mouse2.x, &mouse2.y);
    SDL_Point delta {
        mouse2.x - mouse.x,
        mouse2.y - mouse.y,
    };
    mouse = mouse2;

    if(mode == MM_MOVING) {
        static SDL_FPoint stored {0, 0};
        stored.x -= delta.x / zoom;
        stored.y -= delta.y / zoom;
        
        int x_motion = stored.x;
        camera.x += x_motion;
        stored.x -= x_motion;
        
        int y_motion = stored.y;
        camera.y += y_motion;
        stored.y -= y_motion;

    } else if(mode != MM_NONE)
        apply_action(mouse.x, mouse.y);


    SDL_Point input = keyboard_movement_input();    
    camera.x += input.x * 25;
    camera.y += input.y * 25;
}


void apply_action(int x, int y)
{
    auto& map = current_level->map;

    undo_camera(x, y);

    x = x / block_size.x;
    y = y / block_size.y;

    cout << "Target: " << x << "x" << y << endl;
    Block* block = map.at(x, y);
    if(!block)
        return;

    switch(mode) {
        case MM_CLEARING:
            *block = B_AIR;
            break;

        case MM_PLACING:
            break;

        default:
            break;
    }
}
