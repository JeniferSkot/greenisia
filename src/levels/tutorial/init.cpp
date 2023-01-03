#include "levels/tutorial.hpp"
#include "level.hpp"


Level tutorial::level;


void tutorial::init()
{
    init_map();
    init_background();
}

void tutorial::init_map()
{
    Map map(50, 20);

    for(int y = 0; y < map.height; y++) {
        *map.at(0, y) = B_SOLID;
        *map.at(30, y) = B_SOLID;
    }

    for(int x = 0; x < map.width; x++)
        *map.at(x, 17) = B_SOLID;

    level.map = map;
}

void tutorial::init_background()
{
    Background cave;
    cave.pos = {
        0, 0,
        1848,
        1700
    };

    Layer layers[] {
        { -3, "assets/bg/tutorial/cave/-3.png" },
        { -2, "assets/bg/tutorial/cave/-2.png" },
        { -1, "assets/bg/tutorial/cave/-1.png" },
        { 0, "assets/bg/tutorial/cave/0.png" },
        { 1, "assets/bg/tutorial/cave/1.png" },
        { 2, "assets/bg/tutorial/cave/2.png" },
        { 3, "assets/bg/tutorial/cave/3.png" }
    };
    int count = sizeof(layers) / sizeof(layers[0]);

    cave.layers.insert(
        cave.layers.end(),
        layers,
        layers + count
    );


    level.backgrounds.push_back(cave);
}
