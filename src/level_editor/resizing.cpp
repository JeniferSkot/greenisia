#include "camera.hpp"
#include "level_editor.hpp"
#include "level.hpp"
#include <iostream>

using std::cout;
using std::endl;
using std::flush;

namespace LE = level_editor;

SDL_Point LE::map_edge_markers {50, 50};

bool LE::in_board(int x, int y)
{
    undo_camera(x, y);
    return current_level->map.at(x, y);
}

void LE::resize_map(SDL_Point size)
{
    auto& map = current_level->map;
    if(size.x == map.width && size.y == map.height)
        return;

    if(size.x < map.width || size.y < map.height) {
        cout << endl << endl;
        cout << "***************************" << endl;
        cout << "* WARNING WARNING WARNING *" << endl;
        cout << "***************************" << endl;
        cout << "* You are making the map  *" << endl;
        cout << "* smaller and you will    *" << endl;
        cout << "* lose data if you save.  *" << endl;
        cout << "***************************" << endl;

        if(CONFIRM_DATA_LOSS) {
            cout << "Are you sure? (y/N) " << flush;
            std::string input;
            std::cin >> input;
            if(input != "y") {
                cout << "Resize cancelled." << endl;
                return;
            }
        }
    }

    Map new_map (size.x, size.y);
    for(int y = 0; y < map.height && y < size.y; ++y)
    for(int x = 0; x < map.width && x < size.x; ++x)
        *new_map.at(x, y) = *map.at(x, y);

    current_level->map = new_map;
}

