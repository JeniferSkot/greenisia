#include "story.hpp"

using std::map;


map<fs::path, Character>& characters()
{
    static map<fs::path, Character> _characters;
    return _characters;
}

Character& character(fs::path key)
{
    static Character unknown {
        "E""n""t""i""t""y 3""0""3",
        "as""se""ts/cha""ract""ers/.d""efau""lt.p""ng",
        true
    };

    auto itr = characters().find(key);
    if(itr == characters().end())
        return unknown;
    return itr->second;
}

