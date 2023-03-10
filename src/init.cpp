#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "global.hpp"
#include "render.hpp"

using namespace std;

static const SDL_Point window_size {
    1680 * 7 / 10, // 1176
    1050 * 7 / 10  // 735
};
static int create_window();
static int create_renderer();


int init()
{
    if(SDL_Init(SDL_INIT_VIDEO)) {
        cout << "Error: " << SDL_GetError() << endl;
        return 1;
    }

    if(!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        cout << "Error: " << IMG_GetError() << endl;
        return 1;
    }

    if(TTF_Init()) {
        cout << "Error: " << TTF_GetError() << endl;
        return 1;
    }

    if(create_window())
        return 1;
    if(create_renderer())
        return 1;

    return 0;
}


int create_window()
{
    window = SDL_CreateWindow(
        "My game",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        window_size.x,
        window_size.y,
        0 //SDL_WINDOW_RESIZABLE // flags
    );

    if(window == nullptr) { 
        cout << "Error: " << SDL_GetError() << endl;
        return 1;
    }

    return 0;
}


int create_renderer()
{
    rnd = SDL_CreateRenderer(
        window,
        -1,
        SDL_RENDERER_PRESENTVSYNC
    );

    if(rnd == nullptr) { 
        cout << "Error: " << SDL_GetError() << endl;
        return 1;
    }

    return 0;
}

