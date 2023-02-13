#ifndef INCLUDE_STORY_HPP
#define INCLUDE_STORY_HPP

#include <string>
#include <vector>
#include <map>
#include <filesystem>
#include <SDL2/SDL_rect.h>

using std::string;
using std::vector;
namespace fs = std::filesystem;


struct Character
{
    string name;
    fs::path avatar;
    bool right_side = false;
};

struct Speech
{
    string character;
    string text;
};

struct Story
{
    vector<Speech> speeches;
};


std::map<fs::path, Character>& characters();
Character& character(fs::path);

std::map<fs::path, Story>& stories();
Story& story(fs::path);


void load_characters();
void load_stories();


struct StoryState
{
    bool active = false;
    string story;
    std::size_t phrase;
    float text_len;
    float speed;
};

StoryState& story_state();

void start_story(string name);
bool in_story();

void tick_story(int);
void progress_story();

void render_story();


/* Separate text texture cache. */
struct SDL_Texture;
SDL_Texture* render_story_text(string const& text,
                               SDL_Point* size);
void clear_story_text_cache();

#endif // INCLUDE_STORY_HPP
