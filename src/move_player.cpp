#include "player.hpp"
#include "keyboard.hpp"
#include "level.hpp"
#include <cstdint>
#include <cmath>
#include <iostream>


void move_player(int progress)
{
    auto input = keyboard_movement_input();

    player.old_pos = player.pos;

    move_player_horizontal(progress, input.x);
    player_horizontal_collision();

    move_player_vertical(progress, input.y);
    player_vertical_collision();
}


void move_player_horizontal(int progress, int input_x)
{
    if(input_x == 0)
        return;

    float time = progress / 1000.0f;
    auto& pos = player.pos;

    pos.x += input_x * player.speed * time;

    float delta_x = abs(player.old_pos.x - pos.x);
    player.sprite_time += delta_x;
}

void move_player_vertical(int progress, int input_y)
{
    float time = progress / 1000.0f;

    player.velocity += player.mass * time;
    player.pos.y += player.velocity * time;

    if(input_y < 0)
        player_try_jump();
    else
        player_stop_jump(progress);
}

void player_try_jump()
{
    if(!is_player_on_ground())
        return;

    player.velocity = -player.jump_power;
}

void player_stop_jump(int progress)
{
    if(player.velocity < 0)
        player.velocity /= pow(1.03, progress);
}


void player_horizontal_collision()
{
    auto const& map = current_level->map;
    auto& pos = player.pos;
    auto const& size = player.size;
    auto const& old_pos = player.old_pos;

    if(pos.x < 0)
        pos.x = 0;

    auto bsize = block_size;
    auto map_width = map.width * bsize.x;
    if(pos.x + size.x > map_width)
        pos.x = map_width - size.x;


    int y1 = pos.y / bsize.y;
    int y2 = (pos.y + size.y - 1) / bsize.y;

    float delta_x = pos.x - old_pos.x;
    if(delta_x > 0) { // Right
        int x1 = (old_pos.x + size.x) / bsize.x;
        int x2 = (pos.x + size.x) / bsize.x + 1;
        if(player.velocity == 0)
            x2++;

        for(int x = x1; x <= x2; x++)
        for(int y = y1; y <= y2; y++) {
            Block const* block = map.at(x, y);
            if(!block || !is_solid(*block))
                continue;

            if(y == y2) { // climb
                bool can_go_up = true;
                for(int i = x1; i <= x2; i++) {
                    Block const* b2 = map.at(i, y1 - 1);
                    if(!b2 || is_solid(*b2)) {
                        can_go_up = false;
                        break;
                    }
                }
                if(can_go_up)
                    player.velocity -= player.mass / 10;
            }

            if(pos.x + size.x > x * bsize.x - 1) {
                pos.x = x * bsize.x - size.x - 1;
                return;
            } else break; // Prevent wall climbing
        }
    } else if(delta_x < 0) { // Left
        int x1 = old_pos.x / bsize.x;
        int x2 = pos.x / bsize.x - 1;
        if(player.velocity == 0)
            x2--;

        for(int x = x1; x >= x2; x--)
        for(int y = y1; y <= y2; y++) {
            Block const* block = map.at(x, y);
            if(!block || !is_solid(*block))
                continue;

            if(y == y2) { // climb
                bool can_go_up = true;
                for(int i = x1; i >= x2; i--) {
                    Block const* b2 = map.at(i, y1 - 1);
                    if(!b2 || is_solid(*b2)) {
                        can_go_up = false;
                        break;
                    }
                }
                if(can_go_up)
                    player.velocity -= player.mass / 10;
            }

            if(pos.x < (x + 1) * bsize.x) {
                pos.x = (x + 1) * bsize.x;
                return;
            } else break; // Prevent wall climbing
        }
    }

}


void player_vertical_collision()
{
    auto const& map = current_level->map;
    auto& pos = player.pos;
    auto& velocity = player.velocity;
    auto const& old_pos = player.old_pos;
    auto const& size = player.size;

    if(pos.y < 0) {
        pos.y = 0;
        if(velocity < 0)
            velocity = 0;
    }

    auto bsize = block_size;
    auto map_height = map.height * bsize.y;
    if(pos.y + size.y > map_height) {
        pos.y = map_height - size.y;
        if(velocity > 0)
            velocity = 0;
    }


    int x1 = pos.x / bsize.x;
    int x2 = (pos.x + size.x) / bsize.x;

    float delta_y = pos.y - old_pos.y;
    if(delta_y > 0) { // Down
        int y1 = (old_pos.y + size.y) / bsize.y;
        int y2 = (pos.y + size.y) / bsize.y;

        for(int y = y1; y <= y2; y++)
        for(int x = x1; x <= x2; x++) {
            Block const* block = map.at(x, y);
            if(!block || !is_solid(*block))
                continue;
           
            if(pos.y + size.y > y * bsize.y) {
                pos.y = y * bsize.y - size.y;
                if(velocity > 0)
                    velocity = 0;
                return;
            }
        }
    } else if (delta_y < 0) { // Up
        int y1 = old_pos.y / bsize.y;
        int y2 = pos.y / bsize.y;

        for(int y = y1; y >= y2; y--)
        for(int x = x1; x <= x2; x++) {
            Block const* block = map.at(x, y);
            if(!block || !is_solid(*block))
                continue;

            if(pos.y < (y + 1) * bsize.y) {
                pos.y = (y + 1) * bsize.y;
                if(velocity < 0)
                    velocity = 0;
                return;
            }
        }
    }
}

