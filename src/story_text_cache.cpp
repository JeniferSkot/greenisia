#include "text.hpp"
#include "render.hpp"
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_render.h>
#include <string>
#include <map>

using std::string;

struct CacheData
{
    SDL_Texture* texture = nullptr;
    SDL_Point size {0, 0};
};

static std::map<string, CacheData> cache;


SDL_Texture* render_story_text(string const& text,
                               SDL_Point* size)
{

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

void clear_story_text_cache()
{
    for(auto pair : cache)
        SDL_DestroyTexture(pair.second.texture);

    cache.clear();
}

