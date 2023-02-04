#include "map.hpp"
#include "storage.hpp"
#include <iostream>
#include <fstream>

using std::cout;
using std::endl;


Map load_map(fs::path path)
{
    cout << "Loading map " << path << endl;
    std::ifstream file(path);

    if(!file) {
        cout << "Failed opening map " << path << endl;
        return {};
    }

    uint32_t version = read32(file);
    if(version != MAP_DATA_VERSION) {
        cout << "Invalid map data version!" << endl;
        return {};
    }

    uint32_t w = read32(file);
    uint32_t h = read32(file);
    Map map(w, h);
    for(uint32_t i = 0; i < w*h; i++)
        map.data[i] = static_cast<Block>(read8(file));

    return map;
}

