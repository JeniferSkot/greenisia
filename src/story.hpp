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


#endif // INCLUDE_STORY_HPP
