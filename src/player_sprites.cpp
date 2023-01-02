#include "player.hpp"
#include "textures.hpp"
#include "SDL2/SDL_timer.h"


static vector<string> player_sprites[PS_LAST];
static float frames_per_width[PS_LAST] {
    5,
};
static SDL_Point player_frame_sizes[PS_LAST] {
    {150, 150}
};


void init_player_sprites()
{
    player_sprites[PS_RUNNING] = {
        "assets/player/running/frame0000.png",
        "assets/player/running/frame0001.png",
        "assets/player/running/frame0002.png",
        "assets/player/running/frame0003.png",
        "assets/player/running/frame0004.png",
        "assets/player/running/frame0005.png",
        "assets/player/running/frame0006.png",
        "assets/player/running/frame0007.png",
        "assets/player/running/frame0008.png",
        "assets/player/running/frame0009.png"
    };
}


void load_player_sprites()
{
    vector<string> paths;

    for(auto const& sprites : player_sprites)
    for(string const& path : sprites)
        paths.push_back(path);

    load_textures(paths);
}


SDL_Texture* get_player_sprite(SDL_Point* offset,
                               SDL_Point* frame_size)
{
    auto state = get_player_state();
    auto& sprites = player_sprites[state];
    auto size = player_frame_sizes[state];
    auto frame_count = sprites.size();

    if(offset != nullptr) {
        offset->x = (player.size.x - size.x) / 2;
        offset->y = (player.size.y - size.y) / 2;
    }
    if(frame_size != nullptr) {
        frame_size->x = size.x;
        frame_size->y = size.y;
    }

    auto fpw = frames_per_width[state];
    float lengths = player.sprite_time / size.x;
    auto frame = (int)(lengths * fpw) % frame_count;

    return get_texture(sprites[frame]);
}
