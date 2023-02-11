#include "global.hpp"
#include "events.hpp"
#include "utils.hpp"
#include "mouse.hpp"
#include "map.hpp"
#include "render.hpp"
#include "../block.hpp"
#include "../camera.hpp"
#include <SDL2/SDL_mouse.h>
#include <SDL2/SDL_events.h>

namespace LE = level_editor;

LE::MouseMode LE::mmode = MM_NONE;

SDL_FPoint LE::mouse {0, 0};
SDL_FPoint LE::last_mouse {0, 0};
SDL_FPoint LE::last_target {0, 0};


void LE::on_mousedown(SDL_MouseButtonEvent& ev)
{
    if(in_menu(ev.x, ev.y)) {
        on_menu_click(ev.x, ev.y, ev.button);
        mmode = MM_NONE;
        return;
    }

    switch(ev.button) {
        case SDL_BUTTON_LEFT:
            mmode = MM_BRUSH1;
            if(!in_board(ev.x, ev.y))
                mmode = MM_RESIZING;
            break;

        case SDL_BUTTON_RIGHT:
            mmode = MM_BRUSH2;
            break;

        case SDL_BUTTON_MIDDLE:
            mmode = MM_MOVING;
            break;

        default:
            return;
    }

    mouse.x = ev.x;
    mouse.y = ev.y;
    undo_camera(mouse);
    mouse.x /= block_size.x;
    mouse.y /= block_size.y;


    if(mmode == MM_BRUSH1 || mmode == MM_BRUSH2) {
        auto keys = SDL_GetKeyboardState(nullptr);
        bool shift = keys[SDL_SCANCODE_LSHIFT]
            || keys[SDL_SCANCODE_RSHIFT];

        int brush = mmode == MM_BRUSH1 ? 0 : 1;

        if(!shift) {
            paint(mouse.x, mouse.y, brush);
            return;
        }

        SDL_Point p1 {
            static_cast<int>(last_target.x),
            static_cast<int>(last_target.y)
        };
        SDL_Point p2 {
            static_cast<int>(mouse.x),
            static_cast<int>(mouse.y)
        };
        paint_line(p1, p2, brush);
    }
}


void LE::on_mouseup(SDL_MouseButtonEvent& ev)
{
    switch(mmode)
    {
        case MM_RESIZING:
            resize_map(map_edge_markers);
            break;

        case MM_BRUSH1:
        case MM_BRUSH2:
            last_target.x = ev.x;
            last_target.y = ev.y;
            undo_camera(last_target);
            last_target.x /= block_size.x;
            last_target.y /= block_size.y;
            break;

        default:
            break;
    }

    mmode = MM_NONE;
}


void LE::on_mousewheel(SDL_MouseWheelEvent& ev)
{
    zoom += ev.y * 0.1f;
    if(zoom < 0.2f)
        zoom = 0.2f;
    if(zoom > 1.8f)
        zoom = 1.8f;
}

