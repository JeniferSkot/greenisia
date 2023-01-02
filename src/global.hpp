#ifndef INCLUDE_GLOBAL_HPP
#define INCLUDE_GLOBAL_HPP

#include <SDL2/SDL.h>

extern SDL_Window* window;
extern SDL_Renderer* rnd;

extern bool running;
const SDL_Point block_size {32, 32};

const bool SHOW_DEBUG_GRID = false;


int init();
int create_window();
int create_renderer();


void init_game();

void run();

void handle_events();
void tick(int time_ms);
void render();



#endif // INCLUDE_GLOBAL_HPP
