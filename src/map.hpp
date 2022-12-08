#ifndef INCLUDE_MAP_HPP
#define INCLUDE_MAP_HPP

enum Block
{
    B_AIR,
    B_SOLID,
    B_DANGER,
    B_DEATH,
};


struct Map
{
    const int width;
    const int height;

    Block* data;
    
    Map(int width, int height);
    ~Map();

    Block& at(int x, int y);
};

extern Map map;


void render_map();

#endif // INCLUDE_MAP_HPP
