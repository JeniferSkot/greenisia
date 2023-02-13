#ifndef INCLUDE_LE_RENDER_HPP
#define INCLUDE_LE_RENDER_HPP

#include <SDL2/SDL_rect.h>

namespace level_editor
{
    extern SDL_Rect brush_menu;
    extern SDL_Rect toolbar;
    extern SDL_Rect level_select;
    extern SDL_Rect item_menu;
    extern SDL_Rect item_story_menu;

    void position_menus();

    void render();
    void render_map_border();
    void render_backgrounds();
    void render_brush_menu();
    void render_level_select();
    void render_toolbar();
    void render_item_menu();
    void render_item_story_menu();

    // Store map resize markers position
    extern SDL_Point map_edge_markers;
}

#endif // INCLUDE_LE_RENDER_HPP
