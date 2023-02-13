#ifndef INCLUDE_ITEM_HPP
#define INCLUDE_ITEM_HPP

#include <filesystem>
#include <string>
#include <map>
#include <SDL2/SDL_rect.h>

using std::string;
namespace fs = std::filesystem;


struct Item
{
    string name;
    fs::path sprite;
    SDL_Point size; 
};


std::map<fs::path, Item>& items();
Item& item(fs::path);

void load_items();

void render_items();
void render_item_names();
void render_item_hitboxes();
void render_item_stories();

void collect_items();

#endif // INCLUDE_ITEM_HPP
