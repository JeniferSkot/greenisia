#ifndef INCLUDE_TUTORIAL_HPP
#define INCLUDE_TUTORIAL_HPP

#include "level.hpp"

namespace tutorial
{
    extern Level level;

    void init();
    void init_map();
    void init_background();
    void init_entities();

    void load();
}

#endif // INCLUDE_TUTORIAL_HPP
