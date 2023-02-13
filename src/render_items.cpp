#include "render.hpp"
#include "item.hpp"
#include "level.hpp"
#include "textures.hpp"
#include "camera.hpp"
#include "text.hpp"


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
    auto const& data = current_level->entity_data.items;
    for(auto const& state : data) {
        auto const& entry = ::item(state.item);
        string name = entry.name;

        SDL_Point size;
        auto text = render_text_cached(name, &size);

        SDL_Rect area {
            state.pos.x + entry.size.x / 2,
            state.pos.y,
            size.x, size.y
        };
        apply_camera(area.x, area.y);
        area.x -= size.x / 2;
        area.y -= size.y + 8;

        SDL_RenderCopy(rnd, text, nullptr, &area);
    }
}

void render_item_stories()
{
    auto const& data = current_level->entity_data.items;
    for(auto const& state : data) {
        auto const& entry = ::item(state.item);
        string cue = state.story_cue;

        SDL_Point size;
        auto text = render_text_cached(cue, &size);

        SDL_Rect area {
            state.pos.x + entry.size.x / 2,
            state.pos.y + entry.size.y,
            size.x, size.y
        };
        apply_camera(area.x, area.y);
        area.x -= size.x / 2;
        area.y += 8;

        SDL_RenderCopy(rnd, text, nullptr, &area);
    }
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

