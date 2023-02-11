#include "map.hpp"
#include "../level.hpp"
#include <cmath>

using std::abs;

namespace LE = level_editor;


void LE::paint(int x, int y, int brush)
{
    auto& map = current_level->map;

    Block* block = map.at(x, y);
    if(!block)
        return;

    *block = brushes[brush];
}


void LE::paint_line(SDL_Point p1,
                    SDL_Point p2, int brush)
{
    SDL_Point delta { p2.x - p1.x, p2.y - p1.y };

    if(delta.x == 0 && delta.y == 0) {
        paint(p1.x, p2.x, brush);
        return;
    }

    if(abs(delta.x) > abs(delta.y)) {
        // Rather horizontal line
        if(p2.x < p1.x) {
            // Should go right
            delta.x *= -1;
            delta.y *= -1;
            std::swap(p1, p2);
        }

        for(int x = p1.x; x <= p2.x; x++) {
            int y = p1.y + (x - p1.x) * delta.y/delta.x;
            paint(x, y, brush);
        }
    } else {
        // Rather vertical line
        if(p2.y < p1.y) {
            // Should go down
            delta.x *= -1;
            delta.y *= -1;
            std::swap(p1, p2);
        }

        for(int y = p1.y; y <= p2.y; y++) {
            int x = p1.x + (y - p1.y) * delta.x/delta.y;
            paint(x, y, brush);
        }
    }
}

