#include "map.hpp"
#include "state.hpp"
#include "../level.hpp"
#include "../storage.hpp"
#include "../player.hpp"
#include <fstream>
#include <iostream>

namespace LE = level_editor;
using std::cout;
using std::endl;

static void save_map();
static void save_entity_state();


void LE::save_level()
{
    save_map();
    if(restored_initial_level_state)
        save_entity_state();
}


void save_map()
{
    const int MAP_DATA_VERSION = 1;

    auto& map = current_level->map;
    auto path = current_level->map_file;

    cout << "Saving to " << path << endl;

    std::ofstream file(path);
    if(!file) {
        cout << "Failed opening " << path << endl;
        return;
    }

    write32(file, MAP_DATA_VERSION);
    write32(file, map.width);
    write32(file, map.height);

    int map_size = map.width * map.height;
    for(int i = 0; i < map_size; i++)
        write8(file, map.data[i]);

    if(file.fail())
        cout << "Error while saving " << path << endl;

    file.close();
}


void save_entity_state()
{
    const int LVL_DATA_VERSION = 1;

    auto& level = *current_level;
    auto path = level.entity_data_file;

    cout << "Saving to " << path << endl;

    std::ofstream file(path);
    if(!file) {
        cout << "Failed opening " << path << endl;
        return;
    }

    write32(file, LVL_DATA_VERSION);


    SDL_Point player_pos {
        static_cast<int>(player.pos.x),
        static_cast<int>(player.pos.y)
    };
    write32(file, player_pos.x);
    write32(file, player_pos.y);


    auto const& items = level.entity_data.items;

    write32(file, items.size());

    for(auto const& item : items) {
        write(file, item.item);
        write32(file, item.pos.x);
        write32(file, item.pos.y);
        write(file, item.story_cue);
    }


    if(file.fail())
        cout << "Error while saving " << path << endl;

    file.close();
}

