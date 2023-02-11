#include "render.hpp"
#include "../render.hpp"
#include "../level.hpp"
#include "../camera.hpp"
#include "../textures.hpp"

namespace LE = level_editor;


void LE::render_map_border()
{
    using ::rnd;
    auto& map = current_level->map;

    int width = map.width * block_size.x * zoom;
    int height = map.height * block_size.y * zoom;

    SDL_Point edge {
        map_edge_markers.x * block_size.x,
        map_edge_markers.y * block_size.y
    };

    SDL_Rect top_border {0, -3, width, 3};
    SDL_Rect left_border {-3, 0, 3, height};
    SDL_Rect right_border {
        edge.x, 0,
        3, static_cast<int>(edge.y * zoom)
    };
    SDL_Rect bottom_border {
        0, edge.y,
        static_cast<int>(edge.x * zoom), 3
    };
    apply_camera(top_border.x, top_border.y);
    apply_camera(left_border.x, left_border.y);
    apply_camera(right_border.x, right_border.y);
    apply_camera(bottom_border.x, bottom_border.y);

    SDL_SetRenderDrawColor(rnd, 255, 255, 0, 255);
    SDL_RenderFillRect(rnd, &top_border);
    SDL_RenderFillRect(rnd, &left_border);
    SDL_RenderFillRect(rnd, &right_border);
    SDL_RenderFillRect(rnd, &bottom_border);
}

