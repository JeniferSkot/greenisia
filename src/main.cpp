#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "global.hpp"

using namespace std;

SDL_Window* window = nullptr;
SDL_Renderer* rnd = nullptr;


int main(int, char**)
{
    cout << "Game v0.0" << endl;

    if(init())
        return 1;

    run();

    return 0;
}


