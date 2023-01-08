#ifndef INCLUDE_CAMERA_HPP
#define INCLUDE_CAMERA_HPP

#include "SDL2/SDL_rect.h"

extern SDL_Rect camera;
extern float zoom;

const SDL_FPoint target_camera_size {1680, 1050};


void move_camera(int progress);
SDL_Point get_camera_target();
void resize_camera();
void adjust_zoom();

void apply_camera(SDL_Rect&);
void apply_camera(SDL_Point&);
void apply_camera(int& x, int& y);

// Translates screen to game coordinates.
void undo_camera(SDL_Rect&);
void undo_camera(SDL_Point&);
void undo_camera(int& x, int& y);

#endif // INCLUDE_CAMERA_HPP
