#include "item.hpp"
#include <vector>
#include <fstream>
#include "trim.hpp"
#include <iostream>

using std::vector;
using std::cout;
using std::endl;

static void load_item(fs::path);


void load_items()
{
    const fs::path dir = "assets/items/";
    const string ext = ".item";

    if(!exists(dir) || !is_directory(dir)) {
        cout << "Can not find dir " << dir << endl;
        return;
    }

    fs::directory_iterator end;
    fs::directory_iterator begin(dir);
    for(auto itr = begin; itr != end; itr++) {
        if(itr->path().extension() != ext)
            continue;

        load_item(itr->path());
    }
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

