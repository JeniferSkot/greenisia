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
    level.map_file = "assets/maps/tutorial.map";

    Map map(200, 80);

    for(int y = 0; y < map.height; y++) {
        *map.at(0, y) = B_SOLID;
        *map.at(120, y) = B_SOLID;
    }

    for(int x = 0; x < map.width; x++)
        *map.at(x, 68) = B_SOLID;

    for(int x = 0; x < map.width / 3; x++)
        *map.at(x, 40) = B_SOLID;

    for(int i = 0; i < 30; i++)
        *map.at(80 + i, 68 - i) = B_SOLID;

    level.map = map;
}

void tutorial::init_background()
{
    Background cave;
    cave.pos = {
        0, 0,
        2300,
        1730
    };

    Layer layers[] {
        { -3, "assets/bg/tutorial/cave/_3.png" },
        { -2, "assets/bg/tutorial/cave/_2.png" },
        { -1, "assets/bg/tutorial/cave/_1.png" },
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
