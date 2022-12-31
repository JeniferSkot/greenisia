#ifndef INCLUDE_LEVEL_HPP
#define INCLUDE_LEVEL_HPP

#include "map.hpp"
#include "background.hpp"
#include <vector>

using std::vector;


struct Level
{
    Map map;
    vector<Background> backgrounds;
};


extern Level* current_level;

void init_levels();
void load_backgrounds(Level*);

#endif // INCLUDE_LEVEL_HPP
