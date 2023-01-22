#include "level_editor.hpp"
#include "camera.hpp"
#include "level.hpp"
#include "keyboard.hpp"
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keyboard.h>
#include <cmath>
#include <iostream>

namespace LE = level_editor;
using std::cout;
using std::endl;


enum MouseMode {
    MM_NONE,
    MM_MOVING,
    MM_BRUSH1,
    MM_BRUSH2,
    MM_RESIZING
};

static MouseMode mode = MM_NONE;
static void paint(int x, int y);
static void paint_line(SDL_Point p1, SDL_Point p2);
static SDL_Point mouse {0, 0};
static SDL_Point last_mouseup {0, 0};


void LE::print_help()
{
    cout << endl;
    cout << "====== Level Editor help ======" << endl;
    cout << "Press L to disable level editor" << endl;
    cout << endl;
    cout << "Menu Left Click: action" << endl;
    cout << endl;
    cout << "Left click/drag: place block1" << endl;
    cout << "Right click/drag: place block2" << endl;
    cout << endl;
    cout << "Middle click+drag: move camera" << endl;
    cout << "Movement keys: move camera" << endl;
    cout << endl;
    cout << "Scroll up/down: zoom in/out" << endl;
    cout << endl;
    cout << "Drag outside: resize" << endl;
    cout << "===============================" << endl;
    cout << endl;
}

void LE::on_mousedown(SDL_MouseButtonEvent& ev)
{
    if(in_menu(ev.x, ev.y)) {
        on_menu_click(ev.x, ev.y, ev.button);
        mode = MM_NONE;
        return;
    }


    switch(ev.button) {
        case SDL_BUTTON_LEFT:
            mode = MM_BRUSH1;
            if(!in_board(ev.x, ev.y))
                mode = MM_RESIZING;
            break;
        case SDL_BUTTON_RIGHT:
            mode = MM_BRUSH2;
            break;
        case SDL_BUTTON_MIDDLE:
            mode = MM_MOVING;
            break;
        default:
            return;
    }
    mouse = {ev.x, ev.y};

    if(mode == MM_BRUSH1 || mode == MM_BRUSH2) {
        auto keys = SDL_GetKeyboardState(nullptr);
        bool shift = keys[SDL_SCANCODE_LSHIFT]
            || keys[SDL_SCANCODE_RSHIFT];
        if(shift)
            paint_line(last_mouseup, mouse);
        else
            paint(ev.x, ev.y);
    }
}

void LE::on_mouseup(SDL_MouseButtonEvent& ev)
{
    if(mode == MM_RESIZING)
        resize_map(map_edge_markers);

    mode = MM_NONE;

    if(!in_menu(ev.x, ev.y))
        last_mouseup = {ev.x, ev.y};
}

void LE::on_mousewheel(SDL_MouseWheelEvent& ev)
{
    zoom += ev.y * 0.1f;
    if(zoom < 0.3f)
        zoom = 0.3f;
    if(zoom > 1.8f)
        zoom = 1.8f;
}


void LE::tick(int)
{
    SDL_Point mouse2;
    SDL_GetMouseState(&mouse2.x, &mouse2.y);
    SDL_Point delta {
        mouse2.x - mouse.x,
        mouse2.y - mouse.y,
    };

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

    } else if(mode == MM_BRUSH1 || mode == MM_BRUSH2)
        paint_line(mouse, mouse2);

    if(mode == MM_RESIZING) {
        static SDL_FPoint stored {0, 0};
        stored.x += (delta.x / zoom) / block_size.x;
        stored.y += (delta.y / zoom) / block_size.y;
        
        int x_motion = stored.x;
        map_edge_markers.x += x_motion;
        stored.x -= x_motion;
        
        int y_motion = stored.y;
        map_edge_markers.y += y_motion;
        stored.y -= y_motion;
    } else {
        auto& map = current_level->map;
        map_edge_markers.x = map.width;
        map_edge_markers.y = map.height;
    }


    SDL_Point input = keyboard_movement_input();    
    camera.x += input.x * 25;
    camera.y += input.y * 25;

    position_menus();

    mouse = mouse2;
}


void paint(int x, int y)
{
    auto& map = current_level->map;

    undo_camera(x, y);

    x = x / block_size.x;
    y = y / block_size.y;

    Block* block = map.at(x, y);
    if(!block)
        return;

    switch(mode) {
        case MM_BRUSH1:
            *block = LE::brushes[0];
            break;

        case MM_BRUSH2:
            *block = LE::brushes[1];
            break;

        default:
            break;
    }
}


void paint_line(SDL_Point p1, SDL_Point p2)
{
    auto& map = current_level->map;

    undo_camera(p1);
    p1.x = p1.x / block_size.x;
    p1.y = p1.y / block_size.y;

    undo_camera(p2);
    p2.x = p2.x / block_size.x;
    p2.y = p2.y / block_size.y;


    using std::abs;

    SDL_Point delta { p2.x - p1.x, p2.y - p1.y };

    if(delta.x == 0 && delta.y == 0) {
        Block* block = map.at(p1.x, p1.y);
        if(!block)
            return;

        switch(mode) {
            case MM_BRUSH1:
                *block = LE::brushes[0];
                return;

            case MM_BRUSH2:
                *block = LE::brushes[1];
                return;

            default:
                return;
        }
    }

    if(abs(delta.x) > abs(delta.y)) {
        // Horizontal line
        if(p2.x < p1.x) {
            // Should go right
            delta.x *= -1;
            delta.y *= -1;
            std::swap(p1, p2);
        }

        for(int x = p1.x; x <= p2.x; x++) {
            int y = p1.y + (x - p1.x) * delta.y/delta.x;
            Block* block = map.at(x, y);
            if(!block)
                continue;

            switch(mode) {
                case MM_BRUSH1:
                    *block = LE::brushes[0];
                    break;

                case MM_BRUSH2:
                    *block = LE::brushes[1];
                    break;

                default:
                    break;
            }
        }
    } else {
        // Vertical line
        if(p2.y < p1.y) {
            // Should go down
            delta.x *= -1;
            delta.y *= -1;
            std::swap(p1, p2);
        }

        for(int y = p1.y; y <= p2.y; y++) {
            int x = p1.x + (y - p1.y) * delta.x/delta.y;
            Block* block = map.at(x, y);
            if(!block)
                continue;

            switch(mode) {
                case MM_BRUSH1:
                    *block = LE::brushes[0];
                    break;

                case MM_BRUSH2:
                    *block = LE::brushes[1];
                    break;

                default:
                    break;
            }
        }
    }
}
