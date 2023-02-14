#include "story.hpp"
#include "render.hpp"
#include "camera.hpp"
#include "text.hpp"
#include "textures.hpp"
#include "mb_string.hpp"
#include <SDL2/SDL_rect.h>


static void render_frame();
static void render_avatars();
static void render_story_text();
static SDL_Rect get_frame_area();


void render_story()
{
    render_frame();
    render_avatars();
    render_story_text();
}


void render_frame()
{
    auto area = get_frame_area();
    SDL_SetRenderDrawColor(rnd, 0, 0, 0, 195);
    
    SDL_SetRenderDrawBlendMode(rnd, SDL_BLENDMODE_BLEND);
    SDL_RenderFillRect(rnd, &area);
    SDL_SetRenderDrawBlendMode(rnd, SDL_BLENDMODE_NONE);
}

SDL_Rect get_frame_area()
{
    struct {
        bool init = false;
        string story;
        SDL_Point text_size;
    } static cache;

    auto const& state = story_state();

    if(!cache.init || cache.story != state.story) {
        cache.init = true;
        auto const& story = ::story(state.story);
        cache.story = state.story;

        cache.text_size = {0, 0};

        for(auto const& speech : story.speeches) {
            auto size = get_text_size(speech.text);
            if(cache.text_size.x < size.x)
                cache.text_size.x = size.x;
            if(cache.text_size.y < size.y)
                cache.text_size.y = size.y;
        }

        // Add name height + 24px distance 
        auto line_size = get_text_size("ZAT");
        cache.text_size.y += 24 + line_size.y;
    }

    /* The width contains twice the user frame, which
     * is camera.h / 4 so that text stays centered. */
    SDL_Rect area {
        camera.w / 2,
        camera.h * 3 / 4 - 32,
        cache.text_size.x + camera.h / 2 + 24,
        std::max(cache.text_size.y, camera.h / 4 + 16)
    };

    area.x -= area.w / 2;

    return area;
}


void render_avatars()
{
    const string characters_base = "assets/characters/";
    auto const& state = ::story_state();
    auto const phrase = state.phrase;
    auto const& story = ::story(state.story);
    auto const& speech = story.speeches[phrase];
    auto const& speaker = ::character
        (characters_base + speech.character + ".chr");
    auto texture = get_texture(speaker.avatar);
    auto const& name = speaker.name;

    auto area = get_frame_area();

    SDL_Rect dest {
        speaker.right_side
            ? (area.x + area.w - 8 - camera.h / 4)
            : (area.x + 8),
        area.y + 8,
        camera.h / 4,
        camera.h / 4
    };

    if(speaker.right_side)
        SDL_RenderCopyEx(rnd, texture,
                         nullptr, &dest,
                         0, nullptr,
                         SDL_FLIP_HORIZONTAL);
    else
        SDL_RenderCopy(rnd, texture, nullptr, &dest);

    /* Border */ {
        SDL_SetRenderDrawColor(rnd, 0, 0, 0, 255);

        dest.x -= 1; dest.y -= 1;
        dest.w += 2; dest.h += 2;
        SDL_RenderDrawRect(rnd, &dest);

        dest.x -= 1; dest.y -= 1;
        dest.w += 2; dest.h += 2;
        SDL_RenderDrawRect(rnd, &dest);

        dest.x += 2; dest.y += 2;
        dest.w -= 4; dest.h -= 4;
    }

    /* Name */ {
        SDL_Point name_size;
        auto name_tex = render_text_cached
            (name, &name_size);

        SDL_Rect dest2 {
            speaker.right_side
                ? (dest.x - name_size.x - 24)
                : (dest.x + dest.w + 24),
            area.y + 8,
            name_size.x,
            name_size.y
        };

        SDL_RenderCopy(rnd, name_tex, nullptr, &dest2);
    }
}


void render_story_text()
{
    const string characters_base = "assets/characters/";
    auto const& state = ::story_state();
    auto const phrase = state.phrase;
    auto const& story = ::story(state.story);
    auto const& speech = story.speeches[phrase];
    auto const& speaker = ::character
        (characters_base + speech.character + ".chr");
    auto const& name = speaker.name;

    size_t len = static_cast<size_t>(state.text_len);
    string text = mb_substr(speech.text, 0, len);

    SDL_Point name_size;
    render_text_cached(name, &name_size);

    SDL_Point size;
    auto texture = render_story_text(text, &size);

    auto area = get_frame_area();

    SDL_Rect dest {
        speaker.right_side
            ? (area.x + 24)
            : (dest.x + 24),
        area.y + 8 + name_size.y + 24,
        size.x,
        size.y
    };

    SDL_RenderCopy(rnd, texture, nullptr, &dest);
}

