#ifndef INCLUDE_TEXTURES_HPP
#define INCLUDE_TEXTURES_HPP

#include <vector>
#include <string>

using std::vector;
using std::string;
struct SDL_Texture;


bool is_texture_loaded(string const& path);
void load_textures(vector<string> const& paths);
void load_texture(string const& paths);
void clear_textures();

SDL_Texture* get_texture(string const& path);


#endif // INCLUDE_TEXTURES_HPP
