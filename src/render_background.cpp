#include "render.hpp"
#include "camera.hpp"
#include "background.hpp"
#include "level.hpp"
#include "textures.hpp"
#include <SDL2/SDL.h>

#include <iostream>
using std::endl;
using std::cout;


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

    

    //float ws = 1.0 * bg.pos.w / target_camera_size.x;
    //float hs = 1.0 * bg.pos.h / target_camera_size.y;
        //dest.x += ws * scale;
        //dest.y += hs * scale;


        float x_pos = (float)dest.x / camera.w;
        float y_pos = (float)dest.y / camera.h;


        dest.x += scale * dest.w * x_pos;
        dest.y += scale * dest.h * y_pos;

        auto img = get_texture(layer.second);
        SDL_RenderCopy(rnd, img, nullptr, &dest);
    }
}
