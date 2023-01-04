#ifndef INCLUDE_LEVEL_EDITOR_HPP
#define INCLUDE_LEVEL_EDITOR_HPP

struct SDL_MouseButtonEvent;
struct SDL_MouseMotionEvent;

namespace level_editor
{
#ifdef LEVEL_EDITOR
    extern bool active;
#else
    const bool active = false;
#endif


    void on_mousedown(SDL_MouseButtonEvent&);
    void on_mouseup(SDL_MouseButtonEvent&);
    void on_mousemotion(SDL_MouseMotionEvent&);
}

#endif // INCLUDE_LEVEL_EDITOR_HPP
