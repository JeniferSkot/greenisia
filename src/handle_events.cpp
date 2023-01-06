#include "global.hpp"
#include "level_editor.hpp"
#include "render.hpp"
#include <SDL2/SDL.h>
#include <iostream>

namespace LE = level_editor;
using std::cout;
using std::endl;


static void on_keydown(SDL_KeyboardEvent&);

void handle_events()
{
    SDL_Event ev;
    while(SDL_PollEvent(&ev)) {
        switch(ev.type) {

        case SDL_QUIT:
            running = false;
            break;


        case SDL_MOUSEBUTTONDOWN:
            if(LE::active)
                LE::on_mousedown(ev.button);
            break;

        case SDL_MOUSEBUTTONUP:
            if(LE::active)
                LE::on_mouseup(ev.button);
            break;

        case SDL_MOUSEMOTION:
            if(LE::active)
                LE::on_mousemotion(ev.motion);
            break;


        case SDL_KEYDOWN:
            on_keydown(ev.key);
            break;
        }
    }
}


void on_keydown(SDL_KeyboardEvent& ev)
{
    [[maybe_unused]]
    const auto scancode = ev.keysym.scancode;

#ifdef DEBUG_GRID
    if(scancode == SDL_SCANCODE_G) {
        show_debug_grid = !show_debug_grid;
        if(show_debug_grid)
            cout << "Debug Grid: on" << endl;
        else
            cout << "Debug Grid: off" << endl;
    }
#endif

#ifdef LEVEL_EDITOR
    if(scancode == SDL_SCANCODE_L) {
        LE::active = !LE::active;
        if(LE::active) {
            static bool first_time = true;
            if(first_time)
                LE::print_help();
            first_time = false;

            cout << "Level Editor: on" << endl;
            if(!show_debug_grid) {
                show_debug_grid = true;
                cout << "Debug Grid: on" << endl;
            }
        } else {
            cout << "Level Editor: off" << endl;
        }
    }
#endif
}
