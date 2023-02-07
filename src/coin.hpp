#ifndef INCLUDE_COIN_HPP
#define INCLUDE_COIN_HPP

#include <list>
#include <SDL2/SDL_rect.h>

using std::list;

void spawn_coin(int x, int y);
void spawn_coins(int x, int y, int count);


struct Coin
{
    Coin(Coin const&) = default;
    Coin& operator =(Coin const&) = default;

    SDL_FRect pos {0, 0, 16, 20}; // 4x5
    SDL_FPoint last_pos;
    SDL_FPoint velocity {200, 100}; // * [-1, 1)
    float mass = 500;

    int age = 2048; // * [0, 1)
    float frame_time = 150; // * [0.9;1.1)

private:
    Coin(int x, int y);
    friend void spawn_coin(int x, int y);
};

list<Coin>& coins();
int collected_coins();

void move_coins(int progress);
void progress_coin_animation(int progress);
void collect_coins();

void render_coins();

void load_coin_sprites();

#endif // INCLUDE_COIN_HPP
