#include "render.hpp"
#include "../block.hpp"
#include "../camera.hpp"

namespace LE = level_editor;


void LE::position_menus()
{
    /* Brushes */
    int count = B_LAST;
    int rows = count / 10 + 1;
    int cols = std::min(10, count);

    brush_menu.w = (8 + 48) * cols + 8;
    brush_menu.h = (8 + 48) * rows + 8;


    /* Tools */
    toolbar.x = camera.w - toolbar.w - 8;

    /* Level Select */
    level_select.y = camera.h - level_select.h - 8;
}

