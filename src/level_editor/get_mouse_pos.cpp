#include "utils.hpp"
#include "mouse.hpp"
#include "../camera.hpp"
#include "../block.hpp"
#include <SDL2/SDL_mouse.h>

namespace LE = level_editor;


SDL_FPoint LE::get_mouse_pos()
{
    SDL_Point mouse_i;
    SDL_GetMouseState(&mouse_i.x, &mouse_i.y);
    SDL_FPoint mouse {
        static_cast<float>(mouse_i.x),
        static_cast<float>(mouse_i.y)
    };

    undo_camera(mouse);
    mouse.x /= block_size.x;
    mouse.y /= block_size.y;

    return mouse;
}

