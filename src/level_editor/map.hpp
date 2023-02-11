#ifndef INCLUDE_LE_MAP_HPP
#define INCLUDE_LE_MAP_HPP

#include "../block.hpp"

namespace level_editor
{
    extern Block brushes[2];

    // current_level->map.at(x, y) = brushes[brush]
    // removed undo_camera
    // removed brush taken from mouse mode
    void paint(int x, int y, int brush);
    void paint_line(SDL_Point p1,
                    SDL_Point p2, int brush);

    void resize_map(SDL_Point size);
}

#endif // INCLUDE_LE_MAP_HPP
