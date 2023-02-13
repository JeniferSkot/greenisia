#include "render.hpp"
#include "item_menu.hpp"

namespace LE = level_editor;

SDL_Rect LE::brush_menu { 8, 8, 0, 0 };
SDL_Rect LE::toolbar { 0, 8, 96, 48 };
SDL_Rect LE::level_select { 8, 0, 48, 48 };
SDL_Rect LE::item_menu { 0, 0, 0, 0 };
SDL_Rect LE::item_story_menu { 0, 0, 0, 0 };


void LE::render()
{
    render_map_border();
    render_backgrounds();
    render_brush_menu();
    render_level_select();
    render_toolbar();
    if(item_menu_visible())
        render_item_menu();
    if(item_story_menu_visible())
        render_item_story_menu();
}

