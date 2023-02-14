#include "render.hpp"
#include "text.hpp"
#include "camera.hpp"

void render_loading_screen()
{
    resize_camera();

    SDL_SetRenderDrawColor(rnd, 0, 0, 0, 255);
    SDL_RenderClear(rnd);

    SDL_Point size;
    auto text = render_text("Зареждане...", &size);

    SDL_Rect area {
        (camera.w - size.x) / 2,
        (camera.h - size.y) / 2,
        size.x, size.y
    };

    SDL_RenderCopy(rnd, text, nullptr, &area);

    SDL_RenderPresent(rnd);

    SDL_DestroyTexture(text);
}
