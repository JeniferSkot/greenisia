#ifndef INCLUDE_GLOBAL_HPP
#define INCLUDE_GLOBAL_HPP

#include <SDL2/SDL.h>

int init();
void init_game();

void run();
void stop_game();

void handle_events();
void tick(int time_ms);
void render();

struct SDL_MouseButtonEvent;
void mousedown(SDL_MouseButtonEvent& ev);
void mouseup(SDL_MouseButtonEvent& ev);
struct SDL_MouseMotionEvent;
void mousemotion(SDL_MouseMotionEvent& ev);


#endif // INCLUDE_GLOBAL_HPP
