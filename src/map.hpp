#ifndef INCLUDE_MAP_HPP
#define INCLUDE_MAP_HPP

#include "block.hpp"
#include <string>
#include <filesystem>

using std::string;
namespace fs = std::filesystem;


struct Map
{
    int width;
    int height;

    Block* data;
    
    Map();
    Map(int width, int height);
    Map(Map const&);
    Map(Map&& other);
    ~Map();

    Map& operator =(Map const&);

    Block* at(int x, int y);
    Block const* at(int x, int y) const;
};


void render_map();

Map load_map(fs::path path);

#endif // INCLUDE_MAP_HPP
