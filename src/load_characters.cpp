#include "story.hpp"
#include "textures.hpp"
#include "trim.hpp"
#include <vector>
#include <fstream>
#include <iostream>

using std::vector;
using std::cout;
using std::endl;

static void load_character(fs::path);
static void load_character_sprites();


void load_characters()
{
    const fs::path dir = "assets/characters/";
    const string ext = ".chr";

    if(!exists(dir) || !is_directory(dir)) {
        cout << "Can not find dir " << dir << endl;
        return;
    }

    cout << "Loading characters" << endl;

    fs::directory_iterator end;
    fs::directory_iterator begin(dir);
    for(auto itr = begin; itr != end; itr++) {
        if(itr->path().extension() != ext)
            continue;

        load_character(itr->path());
    }

    load_character_sprites();
}


void load_character(fs::path path)
{
    cout << "Loading character " << path << endl;
    std::ifstream file(path);

    if(!file) {
        cout << "Failed reading chr " << path << endl;
        return;
    }

    vector<string> input;
    for (string line; std::getline(file, line); )
        input.push_back(line);

    if(input.size() < 2) {
        cout << "Too less chr lines: " << path << endl;
        return;
    }

    Character chr {
        trim(input[0]),
        trim(input[1])
    };
    if(trim(input[2]) == ":right")
        chr.right_side = true;

    if(!chr.avatar.empty() && !fs::exists(chr.avatar))
        chr.avatar = "assets/characters" / chr.avatar;

    if(!fs::exists(chr.avatar)) {
        cout << "Missing character avatar: ";
        cout << chr.avatar << endl;
        return;
    }

    characters().emplace(path, chr);
}


static void load_character_sprites()
{
    vector<string> avatars;
    for(auto const& pair : characters())
        avatars.push_back(pair.second.avatar);

    Character& def_chr = character("");
    if(!def_chr.avatar.empty())
        avatars.push_back(def_chr.avatar);

    load_textures(avatars);
}

