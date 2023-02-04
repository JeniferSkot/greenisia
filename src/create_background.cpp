/* Loads background manifest file.
 * Currently layer order is determined by filenames */

#include "background.hpp"
#include <fstream>
#include <iostream>
#include <SDL2/SDL_rect.h>

typedef Background::Layer Layer;
using std::cout;
using std::endl;


static SDL_Rect parse_area(string magick_format);
static int get_z_index(fs::path image);


Background create_background(fs::path const& path)
{
    cout << "Loading bg manifest " << path << endl;
    std::ifstream manifest(path);

    if(!manifest) {
        cout << "Failed opening bgman: " << path << endl;
        return {};
    }

    string img, area;

    manifest >> area;
    SDL_Rect bg_pos = parse_area(area);
    vector<Layer> layers;

    while(!manifest.eof()) {
        manifest >> img >> area;
        SDL_Rect pos = parse_area(area);
        int index = get_z_index(img);

        Layer layer {
            fs::path("assets/bg") / img,
            pos, index
        };
        layers.push_back(layer);
    }


    Background bg {bg_pos, layers};

    return bg;
}


/* Transform {w}x{h}+{x}+{y} into SDL_Rect */
SDL_Rect parse_area(string input)
{
    SDL_Rect area;
    size_t start = 0;
    size_t pos = 0;

    while(input[pos] != 'x') 
        pos++;

    area.w = std::stoi(input.substr(start, pos - start));
    start = ++pos;

    while(input[pos] != '+')
        pos++;

    area.h = std::stoi(input.substr(start, pos - start));
    start = ++pos;

    while(input[pos] != '+')
        pos++;

    area.x = std::stoi(input.substr(start, pos - start));
    start = ++pos;

    area.y = std::stoi(input.substr(pos));

    return area;
}


static int get_z_index(fs::path image)
{
    string name = image.stem();
    if(name[0] == '_')
        name[0] = '-';

    return stoi(name);
}


