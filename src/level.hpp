#ifndef INCLUDE_LEVEL_HPP
#define INCLUDE_LEVEL_HPP

#include "map.hpp"

struct Level
{
    Map map;
};


extern Level* current_level;

void init_levels();

#endif // INCLUDE_LEVEL_HPP
