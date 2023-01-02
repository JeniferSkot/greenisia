#ifndef INCLUDE_PLAYER_HPP
#define INCLUDE_PLAYER_HPP

#include <SDL2/SDL_rect.h>
struct SDL_Texture;


struct Player
{
    SDL_FPoint pos;
    SDL_FPoint old_pos;
    SDL_Point size {200, 300};
    float speed = 1300;
    float velocity = 0;
    float mass = 750;
    float jump_power = 550;
    float sprite_time = 0;
};

extern Player player;

enum PlayerState
{
    PS_RUNNING,

    PS_LAST
};


void move_player(int progress);
void render_player();

void init_player_sprites();
void load_player_sprites();

PlayerState get_player_state();
SDL_Texture* get_player_sprite(SDL_Point* offset,
                               SDL_Point* frame_size);

#endif // INCLUDE_PLAYER_HPP
