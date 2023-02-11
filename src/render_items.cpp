#include "render.hpp"
#include "item.hpp"
#include "level.hpp"
#include "textures.hpp"
#include "camera.hpp"


void render_items()
{
    auto const& data = current_level->entity_data.items;
    for(auto const& state : data) {
        auto const& entry = ::item(state.item);
        auto texture = get_texture(entry.sprite);
        SDL_Rect area {
            state.pos.x,
            state.pos.y,
            entry.size.x,
            entry.size.y
        };
        apply_camera(area);

        SDL_RenderCopy(rnd, texture, nullptr, &area);
    }
}

void render_item_names()
{

}

void render_item_hitboxes()
{
    auto const& data = current_level->entity_data.items;
    for(auto const& state : data) {
        auto const& entry = ::item(state.item);
        SDL_Rect area {
            state.pos.x,
            state.pos.y,
            entry.size.x,
            entry.size.y
        };
        apply_camera(area);

        SDL_SetRenderDrawColor(rnd, 0, 0, 255, 255);
        SDL_RenderDrawRect(rnd, &area);
    }
}

