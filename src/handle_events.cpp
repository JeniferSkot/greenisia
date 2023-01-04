#include "global.hpp"
#include "level_editor.hpp"
#include <SDL2/SDL.h>
#include <iostream>

namespace LE = level_editor;
using std::cout;
using std::endl;


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

        case SDL_KEYDOWN: {
        #ifdef LEVEL_EDITOR
            auto scancode = ev.key.keysym.scancode;
            if(scancode == SDL_SCANCODE_L) {
                LE::active = !LE::active;
                if(LE::active)
                    cout << "Level Editor: on" << endl;
                else
                    cout << "Level Editor: off" << endl;
            }
        #endif
           break;
        }

        }
    }
}

