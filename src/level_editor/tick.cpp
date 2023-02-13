#include "tick.hpp"
#include "global.hpp"
#include "config.hpp"
#include "map.hpp"
#include "render.hpp"
#include "mouse.hpp"
#include "utils.hpp"
#include "../block.hpp"
#include "../camera.hpp"
#include "../level.hpp"
#include "../keyboard.hpp"
#include "../player.hpp"
#include <SDL2/SDL_mouse.h>
#include <SDL2/SDL_keyboard.h>

namespace LE = level_editor;

SDL_Point LE::last_screen_mouse {0, 0};


void LE::tick_moving(int)
{
    SDL_Point screen_mouse;
    SDL_GetMouseState(&screen_mouse.x,
                      &screen_mouse.y);

    SDL_FPoint delta {
        static_cast<float>
            (screen_mouse.x - last_screen_mouse.x),
        static_cast<float>
            (screen_mouse.y - last_screen_mouse.y)
    };

    static SDL_FPoint stored {0, 0};
    stored.x -= delta.x / zoom;
    stored.y -= delta.y / zoom;

    int x_motion = stored.x;
    camera.x += x_motion;
    stored.x -= x_motion;

    int y_motion = stored.y;
    camera.y += y_motion;
    stored.y -= y_motion;
}

void LE::tick_painting(int, int brush)
{
    SDL_Point p1 {
        static_cast<int>(mouse.x),
        static_cast<int>(mouse.y)
    };
    SDL_Point p2 {
        static_cast<int>(last_mouse.x),
        static_cast<int>(last_mouse.y)
    };

    paint_line(p1, p2, brush);
}

void LE::tick_resizing(int)
{
    SDL_FPoint delta {
        mouse.x - last_mouse.x,
        mouse.y - last_mouse.y
    };

    static SDL_FPoint stored {0, 0};
    stored.x += delta.x;
    stored.y += delta.y;
    
    int x_motion = stored.x;
    map_edge_markers.x += x_motion;
    stored.x -= x_motion;
    
    int y_motion = stored.y;
    map_edge_markers.y += y_motion;
    stored.y -= y_motion;
}

void LE::tick_dragging_player(int)
{
    SDL_FPoint delta {
        mouse.x - last_mouse.x,
        mouse.y - last_mouse.y
    };

    static SDL_FPoint stored {0, 0};
    stored.x += delta.x * block_size.x;
    stored.y += delta.y * block_size.y;
    
    int x_motion = stored.x;
    player.pos.x += x_motion;
    stored.x -= x_motion;
    
    int y_motion = stored.y;
    player.pos.y += y_motion;
    stored.y -= y_motion;
}

void LE::tick_dragging_item(int)
{
    Level& level = *current_level;
    auto& items = level.entity_data.items;
    auto& pos = items[target_item].pos;

    SDL_FPoint delta {
        mouse.x - last_mouse.x,
        mouse.y - last_mouse.y
    };

    static SDL_FPoint stored {0, 0};
    stored.x += delta.x * block_size.x;
    stored.y += delta.y * block_size.y;
    
    int x_motion = stored.x;
    pos.x += x_motion;
    stored.x -= x_motion;
    
    int y_motion = stored.y;
    pos.y += y_motion;
    stored.y -= y_motion;
}

void LE::tick_idle(int)
{ }


void LE::tick_keyboard_movement(int)
{
    SDL_Point input = keyboard_movement_input();    
    float multiplier = 1 / zoom;

    auto keys = SDL_GetKeyboardState(nullptr);
    bool shift = keys[SDL_SCANCODE_LSHIFT]
        || keys[SDL_SCANCODE_RSHIFT];
    if(shift)
        multiplier *= shift_speedup_multiplier;

    camera.x += input.x * block_size.x * multiplier;
    camera.y += input.y * block_size.y * multiplier;
}

void LE::tick_fix_edge_markers(int)
{
    if(mmode == MM_RESIZING)
        return;

    auto& map = current_level->map;
    map_edge_markers.x = map.width;
    map_edge_markers.y = map.height;
}


void LE::tick(int ms)
{
    last_mouse = mouse;
    mouse = get_mouse_pos();

    switch(mmode)
    {
        case MM_MOVING:
            tick_moving(ms);
            break;

        case MM_BRUSH1:
            tick_painting(ms, 0);
            break;
        case MM_BRUSH2:
            tick_painting(ms, 1);
            break;

        case MM_RESIZING:
            tick_resizing(ms);
            break;

        case MM_DRAGGING_PLAYER:
            tick_dragging_player(ms);
            break;
        case MM_DRAGGING_ITEM:
            tick_dragging_item(ms);
            break;

        default:
            tick_idle(ms);
            break;
    }

    tick_keyboard_movement(ms);
    tick_fix_edge_markers(ms);
    position_menus();

    SDL_GetMouseState(&last_screen_mouse.x,
                      &last_screen_mouse.y);
}

