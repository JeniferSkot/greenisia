#include "events.hpp"
#include "mouse.hpp"
#include "item_menu.hpp"
#include "utils.hpp"
#include "state.hpp"
#include <SDL2/SDL_events.h>

namespace LE = level_editor;


void LE::item_mousedown(SDL_MouseButtonEvent& ev)
{
    target_item = get_item_entry_index(ev.x, ev.y);

    if(ev.button == SDL_BUTTON_LEFT) {
        mmode = MM_DRAGGING_ITEM;
    } else if(ev.button == SDL_BUTTON_RIGHT) {
        if(target_item != -1)
            delete_item(target_item);
    } else if(ev.button == SDL_BUTTON_MIDDLE) {
        show_item_story_menu();
    }
}

