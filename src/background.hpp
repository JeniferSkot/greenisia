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
    SDL_Point pos;
    vector<Layer> layers;
};

#endif // INCLUDE_BACKGROUND_HPP
