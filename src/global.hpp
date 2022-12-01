#ifndef INCLUDE_GLOBAL_HPP
#define INCLUDE_GLOBAL_HPP

#include <SDL2/SDL.h>

extern SDL_Window* window;
extern SDL_Renderer* rnd;


int init();
int create_window();
int create_renderer();

#endif // INCLUDE_GLOBAL_HPP
