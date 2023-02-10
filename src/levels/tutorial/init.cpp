#include "levels/tutorial.hpp"
#include "level.hpp"


Level tutorial::level;


void tutorial::init()
{
    init_map();
    init_background();
    init_entities();
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

void tutorial::init_entities()
{
    level.entity_data_file =
        "assets/level_data/tutorial.lvl";

    level.entity_data =
        load_entity_data(level.entity_data_file);
}
