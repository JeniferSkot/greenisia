#include "global.hpp"
#include <cstdint>
#include <SDL2/SDL_keyboard.h>
#include "player.hpp"
#include "coin.hpp"
#include "item.hpp"
#include "story.hpp"
#include "level_editor/global.hpp"
#include "camera.hpp"

namespace LE = level_editor;


void tick(int progress)
{
    if(progress > 30)
        progress = 30;

    resize_camera();

    progress_coin_animation(progress);

    if(LE::active) {
        LE::tick(progress);
    } else {
        if(in_story())
            tick_story(progress);

        move_coins(progress);
        move_player(progress);
        collect_coins();
        collect_items();

        if(camera.w > 0 && camera.h > 0)
            adjust_zoom();
        move_camera(progress);
    }
}

