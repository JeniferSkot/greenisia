#ifndef INCLUDE_LEVEL_HPP
#define INCLUDE_LEVEL_HPP

#include "map.hpp"
#include "background.hpp"
#include "story.hpp"
#include "item.hpp"
#include <vector>
#include <string>
#include <SDL2/SDL_rect.h>

using std::vector;
using std::string;


struct ItemState
{
    fs::path item;
    SDL_Point pos;

    fs::path story_cue = "";

    bool collected = false;
};

struct EntityData
{
    SDL_Point player_pos {0, 0};
    vector<ItemState> items;
};

struct Level
{
    string map_file;
    string entity_data_file;

    Map map;
    vector<Background> backgrounds;

    EntityData entity_data;
};


extern Level* current_level;

void init_levels();
void load_backgrounds(Level*);


EntityData load_entity_data(fs::path);


#endif // INCLUDE_LEVEL_HPP
