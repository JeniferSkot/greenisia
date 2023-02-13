#include "text.hpp"
#include "render.hpp"
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_render.h>
#include <iostream>
#include <string>
#include <map>

using std::cout;
using std::endl;
using std::string;


TTF_Font* font()
{
    static TTF_Font* font = [](){
        const string path = "assets/fonts/"
            "LiberationSerif-Regular.ttf";
            //"comic_shanns_2.ttf";
        const int size = 24;

        cout << "Loading font " << path << endl;
        
        auto _font = TTF_OpenFont(path.c_str(), size);
        if(!_font) {
            cout << "Error opening font!" << endl;
            cout << TTF_GetError() << endl;
        }

        return _font;
    }();

    return font;
}


SDL_Texture* render_text(string const& text,
                         SDL_Point* size)
{
    const SDL_Color white {255, 255, 255, 255};
    auto surface = TTF_RenderUTF8_Blended_Wrapped
        (font(), text.c_str(), white, 0);

    if(surface == nullptr) {
        if(size) {
            size->x = 0;
            size->y = 0;
        }
        cout << "Failed text render: " << text << endl;
        cout << TTF_GetError() << endl;
        return nullptr;
    }

    if(size) {
        size->x = surface->w;
        size->y = surface->h;
    }


    SDL_Texture* texture
        = SDL_CreateTextureFromSurface(rnd, surface);

    if(texture == nullptr) {
        cout << "Can not create text texture: "
             << text << endl;
        cout << SDL_GetError() << endl;
    }

    SDL_FreeSurface(surface);

    return texture;
}

SDL_Point get_text_size(string const& text)
{
    const SDL_Color white {255, 255, 255, 255};
    auto surface = TTF_RenderUTF8_Solid_Wrapped
        (font(), text.c_str(), white, 0);

    if(surface == nullptr) {
        cout << "Failed text render: " << text << endl;
        cout << TTF_GetError() << endl;
        return {0, 0};
    }

    SDL_Point size {
        surface->w,
        surface->h
    };

    SDL_FreeSurface(surface);

    return size;
}

SDL_Texture* render_text_cached(string const& text,
                                SDL_Point* size)
{
    struct CacheData
    {
        SDL_Texture* texture = nullptr;
        SDL_Point size {0, 0};
    };

    static std::map<string, CacheData> cache;

    auto itr = cache.find(text);
    if(itr != cache.end()) {
        if(size)
            *size = itr->second.size;
        return itr->second.texture;
    }

    auto& data  = cache[text];
    data.texture = render_text(text, &data.size);

    if(size)
        *size = data.size;
    return data.texture;
}

