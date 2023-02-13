#include "story.hpp"


StoryState& story_state()
{
    static StoryState _state;
    return _state;
}

bool in_story()
{
    return story_state().active;
}


void start_story(string name)
{
    auto& state = story_state();
    state.active = true;
    state.story = name;
    state.phrase = 0;
}


void progress_story()
{

}


void tick_story()
{

}

