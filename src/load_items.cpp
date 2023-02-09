#include "item.hpp"
#include "textures.hpp"
#include "trim.hpp"
#include <vector>
#include <fstream>
#include <iostream>

using std::vector;
using std::cout;
using std::endl;

static void load_item(fs::path);
static void load_item_sprites();


void load_items()
{
    const fs::path dir = "assets/items/";
    const string ext = ".item";

    if(!exists(dir) || !is_directory(dir)) {
        cout << "Can not find dir " << dir << endl;
        return;
    }

    cout << "Loading items" << endl;

    fs::directory_iterator end;
    fs::directory_iterator begin(dir);
    for(auto itr = begin; itr != end; itr++) {
        if(itr->path().extension() != ext)
            continue;

        load_item(itr->path());
    }

    load_item_sprites();
}

void load_item_sprites()
{
    vector<string> sprites;
    for(auto const& pair : items())
        sprites.push_back(pair.second.sprite);

    Item& def_item = item("");
    if(!def_item.sprite.empty())
        sprites.push_back(def_item.sprite);

    load_textures(sprites);
}


static SDL_Point parse_size(string);

void load_item(fs::path path)
{
    cout << "Loading item " << path << endl;
    std::ifstream file(path);

    if(!file) {
        cout << "Failed reading item " << path << endl;
        return;
    }

    vector<string> input;
    for (string line; std::getline(file, line); )
        input.push_back(line);

    if(input.size() < 3) {
        cout << "Too less item lines: " << path << endl;
        return;
    }

    Item item {
        trim(input[0]),
        trim(input[1]),
        parse_size(trim(input[2]))
    };


    if(!item.sprite.empty() && !fs::exists(item.sprite))
        item.sprite = "assets/items" / item.sprite;

    if(!fs::exists(item.sprite)) {
        cout << "Can not find sprite " << input[0];
        cout << " or " << item.sprite << endl;
        item.sprite = "";
    }


    items().emplace(path, item);
}

// Parses <w>x<h> to SDL_Point
SDL_Point parse_size(string input)
{
    size_t x = 0;
    while(x < input.size() && input[x] != 'x')
        x++;
    if(x == input.size()) {
        cout << "Can not parse size " << input << endl;
        return {32, 32};
    }

    SDL_Point size {
        std::stoi(input.substr(0, x)),
        std::stoi(input.substr(x + 1))
    };

    return size;
}

