#include "level_editor.hpp"
#include "level.hpp"
#include <iostream>

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
    cout << "Save not implemented" << endl;
}
