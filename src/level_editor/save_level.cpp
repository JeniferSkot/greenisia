#include "level_editor.hpp"
#include "level.hpp"
#include "storage.hpp"
#include <iostream>
#include <fstream>

namespace LE = level_editor;
using std::cout;
using std::endl;


void LE::save_level()
{
    save_map();
}


void LE::save_map()
{
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
