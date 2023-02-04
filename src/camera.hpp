#ifndef INCLUDE_CAMERA_HPP
#define INCLUDE_CAMERA_HPP

#include "SDL2/SDL_rect.h"

/* WARNING:
 * Camera's position does not include the current zoom.
 *
 * This means if you need to use both position and size,
 * you need to transform one to match the other.
 * The easiest option is to work with not-zoomed
 * coordinates and divide the size by the zoom factor.
 */
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

void apply_camera(SDL_FRect&);
void apply_camera(SDL_FPoint&);
void apply_camera(float& x, float& y);


// Translates screen to game coordinates.
void undo_camera(SDL_Rect&);
void undo_camera(SDL_Point&);
void undo_camera(int& x, int& y);

void undo_camera(SDL_FRect&);
void undo_camera(SDL_FPoint&);
void undo_camera(float& x, float& y);

#endif // INCLUDE_CAMERA_HPP
