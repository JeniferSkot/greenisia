#include "player.hpp"
#include "textures.hpp"
//#include "SDL2/SDL_timer.h"


static vector<string> player_sprites[PS_LAST];
static float frames_per_width[PS_LAST] {
    5,
};
static SDL_Point player_frame_sizes[PS_LAST] {
    {300, 300},
    {300, 300},
    {300, 300},
    {300, 300},
    {300, 300},
    {300, 300},
    {300, 300},
    {300, 300}
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

    player_sprites[PS_WALKING] = {
        "assets/player/walking/frame0000.png",
        "assets/player/walking/frame0001.png",
        "assets/player/walking/frame0002.png",
        "assets/player/walking/frame0003.png",
        "assets/player/walking/frame0004.png",
        "assets/player/walking/frame0005.png",
        "assets/player/walking/frame0006.png",
        "assets/player/walking/frame0007.png",
        "assets/player/walking/frame0008.png",
    };

    player_sprites[PS_IDLING] = {
        "assets/player/jumping/start/frame0007.png"
    };

    player_sprites[PS_JUMPING] = {
        "assets/player/jumping/start/frame0000.png",
        "assets/player/jumping/start/frame0001.png",
        "assets/player/jumping/start/frame0002.png",
        "assets/player/jumping/start/frame0003.png",
        "assets/player/jumping/start/frame0004.png",
        "assets/player/jumping/start/frame0005.png",
        "assets/player/jumping/start/frame0006.png",
        "assets/player/jumping/start/frame0007.png"
    };

    player_sprites[PS_LANDING] = {
        "assets/player/jumping/end/frame0016.png",
        "assets/player/jumping/end/frame0017.png",
        "assets/player/jumping/end/frame0018.png",
        "assets/player/jumping/end/frame0019.png",
        "assets/player/jumping/end/frame0020.png"
    };

    player_sprites[PS_RAISING] = {
        "assets/player/jumping/raising/frame0008.png",
        "assets/player/jumping/raising/frame0009.png",
        "assets/player/jumping/raising/frame0010.png",
        "assets/player/jumping/raising/frame0011.png"
    };

    player_sprites[PS_FALLING] = {
        "assets/player/jumping/falling/frame0012.png",
        "assets/player/jumping/falling/frame0013.png",
        "assets/player/jumping/falling/frame0014.png",
        "assets/player/jumping/falling/frame0015.png"
    };

    player_sprites[PS_ATTACKING] = {
        "assets/player/attacking/frame0000.png",
        "assets/player/attacking/frame0001.png",
        "assets/player/attacking/frame0002.png",
        "assets/player/attacking/frame0003.png",
        "assets/player/attacking/frame0004.png",
        "assets/player/attacking/frame0005.png",
        "assets/player/attacking/frame0006.png",
        "assets/player/attacking/frame0007.png",
        "assets/player/attacking/frame0008.png",
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
