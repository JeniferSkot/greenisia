#include "render.hpp"

namespace LE = level_editor;

SDL_Rect LE::brush_menu { 8, 8, 0, 0 };
SDL_Rect LE::toolbar { 0, 8, 96, 48 };
SDL_Rect LE::level_select { 8, 0, 48, 48 };


void LE::render()
{
    render_map_border();
    render_backgrounds();
    render_brush_menu();
    render_level_select();
    render_toolbar();
}

