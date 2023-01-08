#include "camera.hpp"
#include "render.hpp"
#include <cmath>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
EM_JS(int, canvas_get_width, (), {
    return document.getElementById("canvas").offsetWidth;
});

EM_JS(int, canvas_get_height, (), {
    return document.getElementById("canvas").offsetHeight;
});
#endif



void resize_camera()
{
#ifdef __EMSCRIPTEN__
    camera.w = canvas_get_width();
    camera.h = canvas_get_height();
    SDL_SetWindowSize(window, camera.w, camera.h);
#else
    SDL_GetRendererOutputSize(rnd, &camera.w, &camera.h);
#endif
}

void adjust_zoom()
{
    static float old_zoom = zoom;
    zoom = std::fmin(
        camera.w / target_camera_size.x,
        camera.h / target_camera_size.y
    );

    if(old_zoom != zoom) {
        old_zoom = zoom;
    }
}
