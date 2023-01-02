#include "global.hpp"
#include <SDL2/SDL.h>

#ifdef __EMSCRIPTEN__
#include <emscripten/html5.h>
static int ems_game_loop(double, void*); 
#endif

bool running = false;


void run()
{
    running = true;

#ifdef __EMSCRIPTEN__
    emscripten_request_animation_frame_loop
        (&ems_game_loop, nullptr);
#else
    int last_tick = SDL_GetTicks();

    while(running) {
        int now = SDL_GetTicks();
        int progress = now - last_tick;
        last_tick = now;

        handle_events();
        tick(progress);
        render();
    }
#endif
}

#ifdef __EMSCRIPTEN__
int ems_game_loop(double time, void*)
{
    static double last = time;
    int progress = time - last;
    last += progress;

    handle_events();
    tick(progress);
    render();

    return running ? EM_TRUE : EM_FALSE;
}
#endif
