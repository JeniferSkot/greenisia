#ifndef INCLUDE_GLOBAL_HPP
#define INCLUDE_GLOBAL_HPP

#include <SDL2/SDL.h>

int init();
void init_game();

extern bool running;
void run();

void handle_events();
void tick(int time_ms);
void render();



#endif // INCLUDE_GLOBAL_HPP
