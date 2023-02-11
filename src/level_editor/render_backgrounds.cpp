#include "render.hpp"
#include "../render.hpp"

namespace LE = level_editor;


void LE::render_backgrounds()
{
    SDL_Color bg {0, 128, 255, 127};
    SDL_SetRenderDrawColor(rnd, bg.r, bg.g, bg.b, bg.a);

    SDL_SetRenderDrawBlendMode(rnd, SDL_BLENDMODE_BLEND);
    SDL_RenderFillRect(rnd, &brush_menu);
    SDL_RenderFillRect(rnd, &toolbar);
    SDL_RenderFillRect(rnd, &level_select);
    SDL_SetRenderDrawBlendMode(rnd, SDL_BLENDMODE_NONE);
}

