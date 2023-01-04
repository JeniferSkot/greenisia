#ifndef INCLUDE_RENDER_HPP
#define INCLUDE_RENDER_HPP

#include <SDL2/SDL.h>

extern SDL_Window* window;
extern SDL_Renderer* rnd;

const SDL_Point block_size {64, 64};

#ifdef DEBUG_GRID 
extern bool show_debug_grid;
#else
const bool show_debug_grid = false;
#endif

void render();


#endif // INCLUDE_RENDER_HPP
