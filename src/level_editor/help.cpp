#include "level_editor.hpp"
#include <iostream>

namespace LE = level_editor;
using std::cout;
using std::endl;


void LE::print_help()
{
    cout << endl;
    cout << "====== Level Editor help ======" << endl;
    cout << "Press L to disable level editor" << endl;
    cout << endl;
    cout << "Menu Left Click: action" << endl;
    cout << endl;
    cout << "Left click/drag: place block1" << endl;
    cout << "Right click/drag: place block2" << endl;
    cout << endl;
    cout << "Middle click+drag: move camera" << endl;
    cout << "Movement keys: move camera" << endl;
    cout << endl;
    cout << "Scroll up/down: zoom in/out" << endl;
    cout << endl;
    cout << "Drag outside: resize" << endl;
    cout << "===============================" << endl;
    cout << endl;
}

