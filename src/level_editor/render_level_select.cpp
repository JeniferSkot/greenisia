#include "render.hpp"
#include "config.hpp"
#include "../render.hpp"
#include "../textures.hpp"

namespace LE = level_editor;


void LE::render_level_select()
{
    SDL_Rect dest {
        level_select.x, level_select.y,
        48, 48
    };
    SDL_Rect src { 0, 0, 32, 32 };

    auto texture_path = TOOLBAR_TEXTURE;
    if(!is_texture_loaded(texture_path))
        load_texture(texture_path);
    auto texture = get_texture(texture_path);

    SDL_RenderCopy(rnd, texture, &src, &dest);
}

