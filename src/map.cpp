#include "map.hpp"
#include <stdexcept>

Map::Map() :
    width(0), height(0)
{
    data = nullptr;
}

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
    if(data != nullptr)
        delete[] data;
    data = nullptr;
}


Map& Map::operator =(Map const& other)
{
    width = other.width;
    height = other.height;

    if(data != nullptr)
        delete[] data;
    data = nullptr;

    int size = width * height;
    if(size > 0) {
        data = new Block[size];
        std::copy(other.data, other.data + size, data);
    }

    return *this;
}


Block& Map::at(int x, int y)
{
    if(x >= width || y >= height)
        throw std::runtime_error("This is outside of the map.");

    return data[y * width + x];
}

