#include "global.hpp"
#include <cstdint>
#include <SDL2/SDL_keyboard.h>
#include "player.hpp"
#include "level_editor.hpp"
#include "camera.hpp"

namespace LE = level_editor;


void tick(int progress)
{
    if(progress > 30)
        progress = 30;

    resize_camera();

    if(LE::active) {
        LE::tick(progress);
    } else {
        move_player(progress);

        if(camera.w > 0 && camera.h > 0)
            adjust_zoom();
        move_camera(progress);
    }
}

