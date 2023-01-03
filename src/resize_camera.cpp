#include "global.hpp"
#include "camera.hpp"

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
EM_JS(int, canvas_get_width, (), {
    return document.getElementById("canvas").offsetWidth;
});

EM_JS(int, canvas_get_height, (), {
    return document.getElementById("canvas").offsetHeight;
});
#endif


static void adjust_zoom();


void resize_camera()
{
#ifdef __EMSCRIPTEN__
    camera.w = canvas_get_width();
    camera.h = canvas_get_height();
    SDL_SetWindowSize(window, camera.w, camera.h);
#else
    SDL_GetRendererOutputSize(rnd, &camera.w, &camera.h);
#endif

    adjust_zoom();
}

void adjust_zoom()
{
    int target_x = 1920;
    int target_y = 1080;

    float rate = std::min(
        camera.w / target_x,
        camera.h / target_y
    );

    
}
