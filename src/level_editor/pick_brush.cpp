#include "map.hpp"
#include "events.hpp"
#include <algorithm>

namespace LE = level_editor;

Block LE::brushes[2] = {B_SOLID, B_AIR};


void LE::pick_brush(int x, int y, int brush_index)
{
    auto& brush = brushes[brush_index];

    int count = B_LAST;
    int rows = count / 10 + 1;
    int cols = std::min(10, count);

    x -= 4; y -= 4;
    if(x < 0 || y < 0)
        return;

    x = x / (48 + 8);
    y = y / (48 + 8);
    if(x > cols || y > rows)
        return;

    int choice = y * cols + x;
    if(choice < B_LAST)
        brush = static_cast<Block>(choice);
}

