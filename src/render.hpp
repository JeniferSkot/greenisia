#ifndef INCLUDE_RENDER_HPP
#define INCLUDE_RENDER_HPP

#include "story.hpp"
#include <SDL2/SDL_render.h>

struct SDL_Window;

extern SDL_Window* window;
extern SDL_Renderer* rnd;

const bool show_particle_hitboxes = false;

#ifdef LEVEL_EDITOR
    #ifndef DEBUG_GRID
        #define DEBUG_GRID
    #endif
#endif

#ifdef DEBUG_GRID
extern bool show_debug_grid;
#else
const bool show_debug_grid = false;
#endif

void render();

void render_loading_screen();


#endif // INCLUDE_RENDER_HPP
