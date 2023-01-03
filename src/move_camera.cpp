#include "camera.hpp"
#include "player.hpp"
#include "map.hpp"
#include "global.hpp"

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
EM_JS(int, canvas_get_width, (), {
    return document.getElementById("canvas").offsetWidth;
});

EM_JS(int, canvas_get_height, (), {
    return document.getElementById("canvas").offsetHeight;
});
#endif


static void resize_camera();


void move_camera([[maybe_unused]]int progress)
{
    resize_camera();

    camera.x = player.pos.x + player.size.x / 2
                - camera.w / 2;
    camera.y = player.pos.y - camera.h / 2;




    if(camera.x < 0)
        camera.x = 0;

    if(camera.y < 0)
        camera.y = 0;

}


void resize_camera()
{
#ifdef __EMSCRIPTEN__
    camera.w = canvas_get_width();
    camera.h = canvas_get_height();
    SDL_SetWindowSize(window, camera.w, camera.h);
#else
    SDL_GetRendererOutputSize(rnd, &camera.w, &camera.h);
#endif

    // todo: adjust zoom
}
