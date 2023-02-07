#include "render.hpp"
#include "camera.hpp"
#include "coin.hpp"
#include "textures.hpp"
#include <SDL2/SDL.h>

void progress_coin_animation(int ms)
{
    for(Coin& coin : coins())
        coin.age += ms;
}


static SDL_Point frame_size {64, 80};
static int frame_count = 4;
static const string path = "assets/items/coin.png";

void load_coin_sprites()
{
    load_texture(path);
}


void render_coins()
{
    for(Coin const& coin : coins()) {
        SDL_Rect area {
            static_cast<int>(coin.pos.x),
            static_cast<int>(coin.pos.y),
            static_cast<int>(coin.pos.w),
            static_cast<int>(coin.pos.h)
        };
        apply_camera(area);

        int frame = static_cast<int>
            (coin.age / coin.frame_time) % frame_count;
        SDL_Rect src {
            frame * frame_size.x,
            0,
            frame_size.x,
            frame_size.y
        };

        auto texture = get_texture(path);
        SDL_RenderCopy(rnd, texture, &src, &area);
    }

    if(show_debug_grid)
    if(show_particle_hitboxes) { // hitboxes
        for(Coin const& coin : coins()) {
            SDL_Rect area {
                static_cast<int>(coin.pos.x),
                static_cast<int>(coin.pos.y),
                static_cast<int>(coin.pos.w),
                static_cast<int>(coin.pos.h)
            };
            apply_camera(area);

            SDL_SetRenderDrawColor(rnd, 255, 255, 0, 255);
            SDL_RenderDrawRect(rnd, &area);
        }
    }
}


void render_coin_twinkles()
{
    const int duration = 1;
    const float interval_multiplier = 32.72;

    for(Coin const& coin : coins()) {
        int interval = static_cast<int>
            (coin.frame_time * interval_multiplier);
        int time = coin.age % interval;
        if(time > duration * coin.frame_time)
            continue;

        int dx = (time * 7) % 2;
        int dy = (time * 3) % 2;

        auto const& pos = coin.pos;
        SDL_Rect area {
            static_cast<int>(pos.x + pos.w / 3) + dx,
            static_cast<int>(pos.y + pos.h / 3) + dy,
            3, 3
        };
        apply_camera(area);

        SDL_SetRenderDrawColor(rnd, 255, 255, 0, 255);
        SDL_RenderDrawRect(rnd, &area);
    }
}

