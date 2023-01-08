#ifndef INCLUDE_BACKGROUND_HPP
#define INCLUDE_BACKGROUND_HPP

#include <string>
#include <vector>
#include <utility>
#include <SDL2/SDL_rect.h>

using std::string;
using std::vector;
using std::pair;

typedef pair<int, string> Layer;

struct Background
{
    SDL_Rect pos;
    vector<Layer> layers;

    float scale = 0.05; // per layer index
};


void render_background(int min, int max);

#endif // INCLUDE_BACKGROUND_HPP
