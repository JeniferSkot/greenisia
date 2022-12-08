#ifndef INCLUDE_PLAYER_HPP
#define INCLUDE_PLAYER_HPP

#include <SDL2/SDL_rect.h>


struct Player
{
    SDL_FPoint pos;
    SDL_Point size {20, 30};
    float speed = 300;
};


extern Player player;


void move_player(int progress);
void render_player();

#endif // INCLUDE_PLAYER_HPP
