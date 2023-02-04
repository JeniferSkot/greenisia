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
    level.map = load_map(level.map_file);
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
