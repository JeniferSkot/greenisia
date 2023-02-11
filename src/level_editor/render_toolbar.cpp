#include "render.hpp"
#include "config.hpp"
#include "../render.hpp"
#include "../textures.hpp"

namespace LE = level_editor;


void LE::render_toolbar()
{
    int line = 2;

    SDL_Rect dest {
        toolbar.x, toolbar.y,
        48 * line, 48
    };
    SDL_Rect src { 32, 0, 32 * line, 32 };

    auto texture_path = TOOLBAR_TEXTURE;
    if(!is_texture_loaded(texture_path))
        load_texture(texture_path);
    auto texture = get_texture(texture_path);

    SDL_RenderCopy(rnd, texture, &src, &dest);
}

