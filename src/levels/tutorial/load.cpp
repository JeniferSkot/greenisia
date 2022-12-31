#include "levels/tutorial.hpp"
#include "level.hpp"
#include "player.hpp"


void tutorial::load()
{
    current_level = &level;

    player.pos.x = 100;
    player.pos.y = 100;

    load_backgrounds(&level);
}
