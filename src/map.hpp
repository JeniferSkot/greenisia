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
    int width;
    int height;

    Block* data;
    
    Map();
    Map(int width, int height);
    ~Map();

    Map& operator =(Map const&);

    Block& at(int x, int y);
};


void render_map();

#endif // INCLUDE_MAP_HPP
