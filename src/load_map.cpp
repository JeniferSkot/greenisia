#include "map.hpp"
#include "storage.hpp"
#include "global.hpp"
#include <iostream>
#include <fstream>

using std::cout;
using std::endl;

static Map load_map1(std::ifstream& file);


Map load_map(fs::path path)
{
    cout << "Loading map " << path << endl;
    std::ifstream file(path);

    if(!file) {
        cout << "Failed opening map " << path << endl;
        return {};
    }

    uint32_t version = read32(file);
    cout << "Map version: " << version << endl;

    switch(version) {
        case 1:
            return load_map1(file);
            break;

        default:
            cout << "Invalid map data version!" << endl;
            stop_game();
            return {};
    }
}


Map load_map1(std::ifstream& file)
{
    uint32_t w = read32(file);
    uint32_t h = read32(file);
    Map map(w, h);
    for(uint32_t i = 0; i < w*h; i++)
        map.data[i] = static_cast<Block>(read8(file));

    return map;
}

