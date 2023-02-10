#ifndef INCLUDE_LE_GLOBAL_HPP
#define INCLUDE_LE_GLOBAL_HPP

struct SDL_MouseButtonEvent;
struct SDL_MouseWheelEvent;

namespace level_editor
{
#ifdef LEVEL_EDITOR
    extern bool active;
#else
    const bool active = false;
#endif

    void init();
    void deinit();

    void render();

    void tick(int progress);

    void on_mousedown(SDL_MouseButtonEvent&);
    void on_mouseup(SDL_MouseButtonEvent&);
    void on_mousewheel(SDL_MouseWheelEvent&);
}

#endif // INCLUDE_LE_GLOBAL_HPP
