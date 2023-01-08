#include "level_editor.hpp"
#include "level.hpp"
#include <iostream>
#include <fstream>

namespace LE = level_editor;
using std::cout;
using std::endl;

static const uint32_t DATA_VERSION = 1;


void LE::save_level()
{
    save_map();
}


static void write32(std::ofstream& file, uint32_t data)
{
    char input[4] {
        static_cast<char>(data >> 24),
        static_cast<char>(data >> 16),
        static_cast<char>(data >> 8),
        static_cast<char>(data)
    };

    file.write(&input[0], 4);
}

static void write8(std::ofstream& file, uint8_t data)
{
    char input = static_cast<char>(data);
    file.write(&input, 1);
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

    write32(file, DATA_VERSION);
    write32(file, map.width);
    write32(file, map.height);

    int map_size = map.width * map.height;
    for(int i = 0; i < map_size; i++)
        write8(file, map.data[i]);

    if(file.fail())
        cout << "Error while saving " << path << endl;

    file.close();
}
