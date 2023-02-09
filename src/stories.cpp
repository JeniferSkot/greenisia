#include "story.hpp"

using std::map;


map<fs::path, Story>& stories()
{
    static map<fs::path, Story> _stories;
    return _stories;
}

Story& story(fs::path key)
{
    static Story unknown {
        vector<Speech> {
            { "ghost",
                "Sadly, this part of the story is... "
                "unfinished."
            },
            { "player",
                "Please call the dev team!"
                " They can help."
            },
        }
    };

    auto itr = stories().find(key);
    if(itr == stories().end())
        return unknown;
    return itr->second;
}

