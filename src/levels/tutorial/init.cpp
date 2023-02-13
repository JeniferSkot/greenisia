#include "levels/tutorial.hpp"
#include "level.hpp"
#include <filesystem>

namespace fs = std::filesystem;


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
    vector<string> area_manifests;

    const fs::path dir = "assets/bg/tutorial/";
    const string ext = ".bgman";

    fs::directory_iterator end;
    fs::directory_iterator begin(dir);
    for(auto itr = begin; itr != end; itr++) {
        if(itr->path().extension() != ext)
            continue;
        area_manifests.push_back(itr->path());
    }

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
