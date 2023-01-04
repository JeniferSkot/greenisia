#include "global.hpp"
#include "camera.hpp"
#include "background.hpp"
#include "level.hpp"
#include "textures.hpp"
#include <SDL2/SDL.h>


void render_background(int min, int max)
{
    for(auto z = min; z <= max; z++)
    for(auto const& bg : current_level->backgrounds)
    for(auto const& layer : bg.layers) {
        if(layer.first != z)
            continue;

        float scale = bg.scale * z;

        SDL_Rect dest {
            bg.pos.x,
            bg.pos.y,
            bg.pos.w,
            bg.pos.h
        };
        apply_camera(dest);

        float x_pos = (float)dest.x / camera.w;
        float y_pos = (float)dest.y / camera.h;


        dest.x += scale * dest.w * x_pos;
        dest.y += scale * dest.h * y_pos;

        auto img = get_texture(layer.second);
        SDL_RenderCopy(rnd, img, nullptr, &dest);
    }
}
