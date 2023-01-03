#ifndef INCLUDE_CAMERA_HPP
#define INCLUDE_CAMERA_HPP

#include "SDL2/SDL_rect.h"

extern SDL_Rect camera;
extern float zoom;


void move_camera(int progress);
SDL_Point get_camera_target();
void resize_camera();

#endif // INCLUDE_CAMERA_HPP
