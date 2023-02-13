#include "global.hpp"
#include "render.hpp"
#include "level_editor/global.hpp"
#include "story.hpp"
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
            stop_game();
            break;


        case SDL_MOUSEBUTTONDOWN:
            if(LE::active)
                LE::on_mousedown(ev.button);
            else
                mousedown(ev.button);
            break;

        case SDL_MOUSEBUTTONUP:
            if(LE::active)
                LE::on_mouseup(ev.button);
            else
                mouseup(ev.button);
            break;

        case SDL_MOUSEWHEEL:
            if(LE::active)
                LE::on_mousewheel(ev.wheel);
            break;

        case SDL_MOUSEMOTION:
            mousemotion(ev.motion);
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

#ifdef QUICK_QUIT
    if(scancode == SDL_SCANCODE_Q) {
        stop_game();
        return;
    }
#endif

#ifdef DEBUG_GRID
    if(scancode == SDL_SCANCODE_G) {
        show_debug_grid = !show_debug_grid;
        if(show_debug_grid)
            cout << "Debug Grid: on" << endl;
        else
            cout << "Debug Grid: off" << endl;
        return;
    }
#endif

#ifdef LEVEL_EDITOR
    if(scancode == SDL_SCANCODE_L ||
       scancode == SDL_SCANCODE_R) {
        LE::active = !LE::active;
        if(LE::active) {
            cout << "Level Editor: on" << endl;
            LE::init();

            if(!show_debug_grid) {
                show_debug_grid = true;
                cout << "Debug Grid: on" << endl;
            }
        } else {
            cout << "Level Editor: off" << endl;
            LE::deinit();
        }
        return;
    }
#endif

    if(in_story())
        progress_story();
}
