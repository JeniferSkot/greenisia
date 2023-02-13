#include "text.hpp"
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;


TTF_Font* font()
{
    static TTF_Font* font = [](){
        const string path = "assets/fonts/"
            "comic_shanns_2.ttf";
        const int size = 16;

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
