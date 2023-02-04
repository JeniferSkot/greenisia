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
    vector<string> area_manifests {
        "assets/bg/tutorial/cave.bgman"
    };

    for(string manifest : area_manifests) {
        Background bg = create_background(manifest);
        level.backgrounds.push_back(bg);
    }
}
