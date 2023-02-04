#ifndef INCLUDE_BACKGROUND_HPP
#define INCLUDE_BACKGROUND_HPP

#include <string>
#include <vector>
#include <utility>
#include <SDL2/SDL_rect.h>
#include <filesystem>

using std::string;
using std::vector;
using std::pair;
namespace fs = std::filesystem;

struct Background
{
    struct Layer;


    SDL_Rect pos {0, 0, 0, 0}; // TODO filter divisions
    vector<Layer> layers;

    float scale = 0.05; // motion per layer index
};

struct Background::Layer
{
    string path;

    SDL_Rect pos;
    int z_index;
};


Background create_background(fs::path const& manifest);


void render_background(int min, int max);

#endif // INCLUDE_BACKGROUND_HPP
