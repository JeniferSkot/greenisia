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
        if(layer.z_index != z)
            continue;

        float scale = 1 + bg.scale * z;

        /* Find positions of bg and layer on camera */
        SDL_FRect area {
            static_cast<float>(bg.pos.x),
            static_cast<float>(bg.pos.y),
            static_cast<float>(bg.pos.w),
            static_cast<float>(bg.pos.h)
        };
        SDL_FRect pos {
            static_cast<float>(layer.pos.x + bg.pos.x),
            static_cast<float>(layer.pos.y + bg.pos.y),
            static_cast<float>(layer.pos.w),
            static_cast<float>(layer.pos.h)
        };

        /* Scale layer based on z index */ {
            pos.x -= pos.w * (scale - 1) / 2;
            pos.y -= pos.h * (scale - 1) / 2;
            pos.w *= scale;
            pos.h *= scale;
        }

        /* Find layer motion range */
        float x_range = area.w * (1 - scale);
        float y_range = area.h * (1 - scale);


        /* Find camera position related to bg
         * 0 - camera is touching left edge from outside
         * 1 - camera is touching right edge from outside
         */
        float x_rate, y_rate;

        /* Horizontal */ {
            int cam_pleft = area.x - camera.w / zoom;
            int cam_pright = area.x + area.w;
            int cam_pwidth = cam_pright - cam_pleft;
            
            float cam_dx = camera.x - cam_pleft;
            // Don't render if camera is outside
            //if(cam_dx < 0 || cam_dx >= cam_pwidth)
            //    continue;

            x_rate = cam_dx / cam_pwidth;
        }

        /* Vertical */ {
            int cam_ptop = area.y - camera.h / zoom;
            int cam_pbottom = area.y + area.h;
            int cam_pheight = cam_pbottom - cam_ptop;
            
            float cam_dy = camera.y - cam_ptop;
            // Don't render if camera is outside
            //if(cam_dy < 0 || cam_dy >= cam_pheight)
            //    continue;

            y_rate = cam_dy / cam_pheight;
        }

        pos.x += x_rate * x_range;
        pos.y += y_rate * y_range;

        SDL_Rect output {
            static_cast<int>(pos.x),
            static_cast<int>(pos.y),
            static_cast<int>(pos.w),
            static_cast<int>(pos.h)
        };

        apply_camera(output);

        auto img = get_texture(layer.path);
        SDL_RenderCopy(rnd, img, nullptr, &output);
    }
}
