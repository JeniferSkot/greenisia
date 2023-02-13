#include "render.hpp"
#include "state.hpp"
#include "../render.hpp"

namespace LE = level_editor;


void LE::render_backgrounds()
{
    SDL_SetRenderDrawColor(rnd, 0, 128, 255, 127);
    SDL_SetRenderDrawBlendMode(rnd, SDL_BLENDMODE_BLEND);

    SDL_RenderFillRect(rnd, &brush_menu);
    SDL_RenderFillRect(rnd, &level_select);

    /* Toolbar useful when editing object state. */ {
        if(restored_initial_level_state)
            SDL_SetRenderDrawColor
                (rnd, 0, 255, 128, 127);

        SDL_RenderFillRect(rnd, &toolbar);
        SDL_RenderFillRect(rnd, &item_menu);
        SDL_RenderFillRect(rnd, &item_story_menu);
    }

    SDL_SetRenderDrawBlendMode(rnd, SDL_BLENDMODE_NONE);
}

