#include "level.hpp"
#include "levels/tutorial.hpp"

Level* current_level = nullptr;


void init_levels()
{
    tutorial::init();


    tutorial::load();
}

