#ifndef INCLUDE_PLAYER_HPP
#define INCLUDE_PLAYER_HPP

#include <SDL2/SDL_rect.h>
struct SDL_Texture;


struct Player
{
    SDL_FPoint pos;
    SDL_FPoint old_pos; // TODO rename to last_pos
    SDL_Point size {200, 300}; // TODO merge with pos
    float speed = 1300;
    float velocity = 0;
    float mass = 4300;
    float jump_power = 1800;
    float sprite_time = 0;
};

extern Player player;

enum PlayerState
{
    PS_RUNNING,

    PS_LAST
};


void move_player(int progress);
void move_player_horizontal(int progress, int input_x);
void move_player_vertical(int progress, int input_y);
void player_try_jump();
void player_stop_jump(int progress);

void player_horizontal_collision();
void player_vertical_collision();

bool is_player_on_ground();


void render_player();
void render_player_hitbox();

void init_player_sprites();
void load_player_sprites();

PlayerState get_player_state();
SDL_Texture* get_player_sprite(SDL_Point* offset,
                               SDL_Point* frame_size);

#endif // INCLUDE_PLAYER_HPP
