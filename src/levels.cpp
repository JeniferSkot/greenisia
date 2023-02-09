#include "textures.hpp"
#include "level.hpp"
#include "levels/tutorial.hpp"
#include <iostream>

using std::cout;
using std::endl;


Level* current_level = nullptr;


void init_levels()
{
    tutorial::init();


    tutorial::load();
}


void load_backgrounds(Level* level)
{
    cout << "Loading level backgrounds" << endl;

    vector<string> paths;

    for(auto const& background : level->backgrounds)
    for(auto const& layer : background.layers) {
        paths.push_back(layer.path);
    }

    load_textures(paths);
}

