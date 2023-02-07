#include "coin.hpp"
#include "level.hpp"
#include "player.hpp"
#include "random.hpp"
#include <cmath>
#include <iostream>

using std::cout;
using std::endl;


static void move_coin(int ms, Coin&);

void move_coins(int ms)
{
    for(Coin& coin : coins())
        move_coin(ms, coin);
}


static void move_coin_horizontal(int ms, Coin&);
static void move_coin_vertical(int ms, Coin&);

static void coin_horizontal_collision(Coin&);
static void coin_vertical_collision(Coin&);

void move_coin(int ms, Coin& coin)
{
    coin.last_pos = {coin.pos.x, coin.pos.y};

    move_coin_horizontal(ms, coin);
    coin_horizontal_collision(coin);

    move_coin_vertical(ms, coin);
    coin_vertical_collision(coin);
}

void move_coin_horizontal(int ms, Coin& coin)
{
    float time = ms / 1000.0f;

    coin.velocity.x *= pow(0.999, ms);
    if(abs(coin.velocity.x) < 0.001)
        coin.velocity.x = 0;

    coin.pos.x += coin.velocity.x * time;
}

void move_coin_vertical(int ms, Coin& coin)
{
    float time = ms / 1000.0f;

    coin.velocity.y += coin.mass * time;
    coin.pos.y += coin.velocity.y * time;
}


void coin_horizontal_collision(Coin& coin)
{
    auto& pos = coin.pos;
    auto& lpos = coin.last_pos;
    auto& velocity = coin.velocity;

    if(pos.x == lpos.x)
        return;

    float dx = pos.x - lpos.x;

    auto const& map = current_level->map;

    /* Map border */ {
        if(pos.x < 0) {
            coin.pos.x = 0;
            if(velocity.x < 0)
                velocity.x = -velocity.x;
        }
        if(pos.x + pos.w > block_size.x * map.width) {
            pos.x = block_size.x * map.width - pos.w;
            if(velocity.x > 0)
                velocity.x = -velocity.x;
        }
    }

    /* Map collision */ {
        auto& bsize = block_size;
        int y1 = pos.y / block_size.y;
        int y2 = (pos.y + pos.h) / block_size.y - 1;

        if(dx > 0) { // right
            int x1 = (lpos.x + pos.w) / bsize.x;
            int x2 = (pos.x + pos.w) / bsize.x;

            for(int x = x1; x <= x2; x++)
            for(int y = y1; y <= y2; y++)
            {
                Block const* block = map.at(x, y);
                if(!block || !is_solid(*block))
                    continue;

                if(pos.x + pos.w > x * bsize.x - 1) {
                    pos.x = x * bsize.x - pos.w - 1;
                    if(velocity.x > 0)
                        velocity.x = -velocity.x;
                } else break; // skip blocks on same x
            }
            
        } else { // left
            int x1 = lpos.x / bsize.x;
            int x2 = pos.x / bsize.x;

            for(int x = x1; x >= x2; --x)
            for(int y = y1; y <= y2; y++)
            {
                Block const* block = map.at(x, y);
                if(!block || !is_solid(*block))
                    continue;

                if(pos.x < (x + 1) * bsize.x) {
                    pos.x = (x + 1) * bsize.x;
                    if(velocity.x < 0)
                        velocity.x = -velocity.x;
                } else break; // skip blocks on same x
            }

        }
    }
}


static void vertical_bounce(Coin& coin)
{
    static std::uniform_real_distribution<float>
        dist(-0.3, -0.6);

    coin.velocity.y *= dist(get_coin_rng());
}

void coin_vertical_collision(Coin& coin)
{
    auto& pos = coin.pos;
    auto& lpos = coin.last_pos;
    auto& velocity = coin.velocity;

    if(pos.y == lpos.y)
        return;

    float dy = pos.y - lpos.y;

    auto const& map = current_level->map;

    /* Map borders */ {
        if(pos.y < 0) {
            pos.y = 0;
            if(velocity.y < 0)
                vertical_bounce(coin);
        }

        auto const& bsize = block_size;
        auto map_height = map.height * bsize.y;
        if(pos.y + pos.h > map_height) {
            pos.y = map_height - pos.h; 
            if(velocity.y > 0)
                vertical_bounce(coin);
        }
    }


    /* Map collision */ {
        auto const& bsize = block_size;
        int x1 = pos.x / bsize.x;
        int x2 = (pos.x + pos.w) / bsize.x;

        if(dy > 0) { // down
            int y1 = (lpos.y + pos.h) / bsize.y;
            int y2 = (pos.y + pos.h) / bsize.y;

            for(int y = y1; y <= y2; y++)
            for(int x = x1; x <= x2; x++) {
                Block const* block = map.at(x, y);
                if(!block || !is_solid(*block))
                    continue;
               
                if(pos.y + pos.h > y * bsize.y) {
                    pos.y = y * bsize.y - pos.h;
                    if(velocity.y > 0)
                        vertical_bounce(coin);
                    return;
                }
            }

        } else { // up
            int y1 = lpos.y / bsize.y;
            int y2 = pos.y / bsize.y;

            for(int y = y1; y >= y2; y--)
            for(int x = x1; x <= x2; x++) {
                Block const* block = map.at(x, y);
                if(!block || !is_solid(*block))
                    continue;

                if(pos.y < (y + 1) * bsize.y) {
                    pos.y = (y + 1) * bsize.y;
                    if(velocity.y < 0)
                        vertical_bounce(coin);
                    return;
                }
            }

        }
    }
}


static int& _collected_coins()
{
    static int collected = 0;
    return collected;
}

int collected_coins()
{
    return _collected_coins();
}


static bool has_player_collision(Coin const&);
void collect_coins()
{
    int last_coins = collected_coins();

    using std::size_t;

    for(size_t i = 0; i < coins().size(); ++i) {
        if(!has_player_collision(coins()[i]))
            continue;

        std::swap(coins()[i], coins().back());
        coins().pop_back();
        _collected_coins()++;
    }

    if(last_coins != collected_coins())
        cout << "Coins: " << collected_coins() << endl;
}


void coin_player_collision(Coin& coin)
{
    if(!has_player_collision(coin))
        return;

    _collected_coins()++;
    cout << "Coins: " << _collected_coins() << endl;
}

static bool has_player_collision(Coin const& coin)
{
    auto const& pos = coin.pos;
    const int range = block_size.x * 2;
    if(pos.x < player.pos.x + player.size.x)
    if(pos.x + pos.w > player.pos.x)
    if(pos.y < player.pos.y + player.size.y + range)
    if(pos.y + pos.h > player.pos.y)
        return true;
    return false;
}


