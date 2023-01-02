#ifndef INCLUDE_PLAYER_HPP
#define INCLUDE_PLAYER_HPP

#include <SDL2/SDL_rect.h>
struct SDL_Texture;


struct Player
{
    SDL_FPoint pos;
    SDL_Point size {100, 150};
    float speed = 450;
    float velocity = 0;
    float mass = 1500;
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
