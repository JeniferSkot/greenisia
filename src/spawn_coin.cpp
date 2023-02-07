#include "coin.hpp"
#include "random.hpp"
#include <iostream>

using std::cout;
using std::endl;


vector<Coin>& coins()
{
    static vector<Coin> _coins;
    return _coins;
}


void spawn_coins(int x, int y, int count)
{
    using dist_t = std::uniform_int_distribution<>;
    dist_t distribution(-5, 5);
    for(int i = 0; i < count; ++i) {
        int dx = distribution(get_coin_rng());
        int dy = distribution(get_coin_rng());
        spawn_coin(x + dx, y + dy);
    }
}

void spawn_coin(int x, int y)
{
    Coin coin(x, y);
    coins().push_back(coin);
}


Coin::Coin(int x, int y)
{
    pos.x = x;
    pos.y = y;
    last_pos.x = x;
    last_pos.y = y;

    using dist_t = std::uniform_real_distribution<float>;

    static dist_t dist1(-1.0f, 1.0f);
    velocity.x *= dist1(get_coin_rng());
    velocity.y *= dist1(get_coin_rng());

    static dist_t dist2(0.9f, 1.1f);
    frame_time *= dist2(get_coin_rng());

    static dist_t dist3(0.0f, 1.0f);
    age *= dist3(get_coin_rng());
}

