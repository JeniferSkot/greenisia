#include "map.hpp"
#include <stdexcept>

Map::Map(int w, int h) :
    width(w),
    height(h)
{
    data = new Block[w * h];

    for(int i = 0; i < w*h; i++)
        data[i] = B_AIR;
}


Map::~Map()
{
    delete[] data;
    data = nullptr;
}


Block& Map::at(int x, int y)
{
    if(x >= width || y >= height)
        throw std::runtime_error("This is outside of the map.");

    return data[y * width + x];
}

