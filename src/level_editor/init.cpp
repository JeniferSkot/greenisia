#include "level_editor/global.hpp"
#include "level_editor.hpp"

namespace LE = level_editor;

#ifdef LEVEL_EDITOR
bool LE::active = false;
#endif


void LE::init()
{
    [[maybe_unused]]
    static bool helper = [](){
        print_help();
        return true;
    }();

    restored_initial_level_state = false;
}

void LE::deinit()
{
    if(restored_initial_level_state)
        restore_current_level_state();
}
