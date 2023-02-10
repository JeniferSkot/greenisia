#include "level.hpp"
#include "storage.hpp"
#include "global.hpp"
#include <fstream>
#include <iostream>

using std::ifstream;
using std::cout;
using std::endl;

static EntityData load_entity_data1(ifstream& file);


EntityData load_entity_data(fs::path path)
{
    cout << "Loading lvl " << path << endl;
    ifstream file(path);

    if(!file) {
        cout << "Failed opening " << path << endl;
        return {};
    }

    uint32_t version = read32(file);
    cout << "Level version: " << version << endl;

    switch(version) {
        case 1:
            return load_entity_data1(file);

        default:
            cout << "Invalid lvl file version!" << endl;
            stop_game();
            return {};
    }
}

EntityData load_entity_data1(ifstream& file)
{
    EntityData result;

    result.player_pos.x = read32(file);
    result.player_pos.y = read32(file);

    size_t item_count = read32(file);
    for(size_t i = 0; i < item_count; i++) {
        string name = read(file);
        int x = read32(file);
        int y = read32(file);
        string story = read(file);

        result.items.push_back({
            name,
            SDL_Point{x, y},
            story
        });
    } 

    return result;
}
