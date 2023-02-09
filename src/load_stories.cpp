#include "story.hpp"
#include "textures.hpp"
#include "trim.hpp"
#include <vector>
#include <fstream>
#include <iostream>

using std::vector;
using std::cout;
using std::endl;

static void load_story(fs::path);


void load_stories()
{
    const fs::path dir = "assets/stories/";
    const string ext = ".act";

    if(!exists(dir) || !is_directory(dir)) {
        cout << "Can not find dir " << dir << endl;
        return;
    }

    cout << "Loading stories" << endl;

    fs::directory_iterator end;
    fs::directory_iterator begin(dir);
    for(auto itr = begin; itr != end; itr++) {
        if(itr->path().extension() != ext)
            continue;

        load_story(itr->path());
    }
}


void load_story(fs::path path)
{
    cout << "Loading story " << path << endl;
    std::ifstream file(path);

    if(!file) {
        cout << "Failed reading story " << path << endl;
        return;
    }


    Story& story = stories()[path];

    string speaker = "";

    for (string line; std::getline(file, line); ) {
        if(line[0] == '#')
            continue;

        if(line[0] == '>') {
            speaker = trim(line.substr(1));
            continue;
        }

        Speech speech {speaker, trim(line)};
        story.speeches.push_back(speech);
    }
}

