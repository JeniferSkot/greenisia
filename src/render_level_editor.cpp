#include "level_editor.hpp"
#include "level.hpp"
#include "render.hpp"
#include "camera.hpp"
#include <SDL2/SDL_events.h>

namespace LE = level_editor;


// Renders block selection
void LE::render()
{
    auto& map = current_level->map;

    int width = map.width * block_size.x * zoom;
    int height = map.height * block_size.y * zoom;

    SDL_Rect top_border {0, -3, width, 3};
    SDL_Rect left_border {-3, 0, 3, height};
    apply_camera(top_border.x, top_border.y);
    apply_camera(left_border.x, left_border.y);

    SDL_SetRenderDrawColor(rnd, 255, 255, 0, 255);
    SDL_RenderFillRect(rnd, &top_border);
    SDL_RenderFillRect(rnd, &left_border);
}
