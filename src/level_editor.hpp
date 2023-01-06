#ifndef INCLUDE_LEVEL_EDITOR_HPP
#define INCLUDE_LEVEL_EDITOR_HPP

#include "block.hpp"
#include <SDL2/SDL_rect.h>

struct SDL_MouseButtonEvent;
struct SDL_MouseMotionEvent;


namespace level_editor
{
#ifdef LEVEL_EDITOR
    extern bool active;
#else
    const bool active = false;
#endif

    extern SDL_Rect menu_area;
    extern Block brush;

    void print_help();

    void on_mousedown(SDL_MouseButtonEvent&);
    void on_mouseup(SDL_MouseButtonEvent&);
    void on_mousemotion(SDL_MouseMotionEvent&);

    void render();
    void tick(int progress);
}

#endif // INCLUDE_LEVEL_EDITOR_HPP
