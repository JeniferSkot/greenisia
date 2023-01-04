#ifndef INCLUDE_CAMERA_HPP
#define INCLUDE_CAMERA_HPP

#include "SDL2/SDL_rect.h"

extern SDL_Rect camera;
extern float zoom;


void move_camera(int progress);
SDL_Point get_camera_target();
void resize_camera();

void apply_camera(SDL_Rect&);
void apply_camera(SDL_Point&);
void apply_camera(int& x, int& y);

#endif // INCLUDE_CAMERA_HPP
