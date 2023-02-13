#ifndef INCLUDE_TEXT_HPP
#define INCLUDE_TEXT_HPP

#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_rect.h>
#include <string>

struct SDL_Texture;

TTF_Font* font();

SDL_Texture* render_text(std::string const& text,
                         SDL_Point* size = 0);
SDL_Point get_text_size(std::string const& text);
SDL_Texture* render_text_cached(std::string const& text,
                                SDL_Point* size = 0);

#endif // INCLUDE_TEXT_HPP
