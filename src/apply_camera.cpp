#include "camera.hpp"

void apply_camera(SDL_Rect& rect)
{
    apply_camera(rect.x, rect.y);
    rect.w *= zoom;
    rect.h *= zoom;
}

void apply_camera(SDL_Point& point)
{
    apply_camera(point.x, point.y);
}

void apply_camera(int& x, int& y)
{
    SDL_Point mid {
        camera.x + camera.w / 2,
        camera.y + camera.h / 2
    };

    x -= mid.x;
    y -= mid.y;

    x *= zoom;
    y *= zoom;

    x += camera.w / 2;
    y += camera.h / 2;

}
