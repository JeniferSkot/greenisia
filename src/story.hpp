#ifndef INCLUDE_STORY_HPP
#define INCLUDE_STORY_HPP

#include <string>
#include <vector>
#include <map>
#include <filesystem>

using std::string;
using std::vector;
namespace fs = std::filesystem;


struct Character
{
    string name;
    fs::path avatar;
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
    int phrase;
};

StoryState& story_state();

void start_story(string name);
bool in_story();

void tick_story();
void progress_story();

void render_story();


#endif // INCLUDE_STORY_HPP
