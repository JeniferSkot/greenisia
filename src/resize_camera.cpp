#include "global.hpp"
#include "camera.hpp"
#include <iostream>

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

    if(camera.w > 0 && camera.h > 9)
        adjust_zoom();
}

void adjust_zoom()
{
    static float old_zoom = zoom;
    zoom = std::min(
        camera.w / target_camera_size.x,
        camera.h / target_camera_size.y
    );

    if(old_zoom != zoom) {
        old_zoom = zoom;
        std::cout << "Zoom: " << zoom << std::endl;
    }
}
