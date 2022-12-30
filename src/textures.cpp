#include "global.hpp"
#include "textures.hpp"
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_render.h>
#include <map>
#include <iostream>

using std::cout;
using std::endl;

static std::map<string, SDL_Texture*> textures;


static SDL_Surface* create_surface(string const& path)
{
    SDL_Surface* surface = IMG_Load(path.c_str());
    if(surface == nullptr) {
        cout << "Can not load asset: " << path << endl;
        cout << IMG_GetError() << endl;
    }

    return surface;
}

static SDL_Texture* create_texture(string const& path)
{
    SDL_Surface* surface = create_surface(path);
    if(surface == nullptr)
        return nullptr;

    SDL_Texture* texture
        = SDL_CreateTextureFromSurface(rnd, surface);

    if(texture == nullptr) {
        cout << "Can not create texture: "
             << path << endl;
        cout << SDL_GetError() << endl;
    }

    SDL_FreeSurface(surface);

    return texture;
}


void load_textures(vector<string> const& paths)
{
    for(string const& path : paths) {
        auto old = textures.find(path);
        if(old != textures.end()) { // Already exists.
            SDL_DestroyTexture(old->second);
            textures.erase(old);
        }

        auto texture = create_texture(path);
        if(texture != nullptr)
            textures[path] = texture;
    }
}

void clear_textures()
{
    for(auto const& pair : textures) {
        SDL_Texture* texture = pair.second;
        SDL_DestroyTexture(texture);
    }

    textures.clear();
}


SDL_Texture* get_texture(string const& path)
{
    auto pair = textures.find(path);
    if(pair == textures.end()) {
        cout << "Requested but never loaded asset:\n ";
        cout << path << endl;
        return nullptr;
    }

    return pair->second;
}

