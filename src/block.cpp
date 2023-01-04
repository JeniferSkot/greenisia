#include "block.hpp"


bool is_solid(Block block)
{
    switch(block)
    {
        case B_AIR:
            return false;

        default:
            return true;
    }
}

