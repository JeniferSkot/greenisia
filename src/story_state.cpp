#include "story.hpp"
#include "mb_string.hpp"
#include <iostream>

using std::cout;
using std::endl;

static float initial_text_speed = 30.0f;
const float ignore_text_mode_activation_speed = 45.0f;
const float initial_speed_increase_factor = 1.0f;


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
    state.text_len = 0;
    state.speed = initial_text_speed;
}


void progress_story()
{
    auto& state = story_state();
    auto& phrase = state.phrase;
    auto const& story = ::story(state.story);
    auto const& speech = story.speeches[phrase];
    auto const& text = speech.text;
    std::size_t len = state.text_len;

    if(len < mb_strlen(text)) {
        state.speed += 4.5;
        float const& inc = initial_speed_increase_factor;
        initial_text_speed += inc;
        return;
    }

    clear_story_text_cache();
    phrase++;
    state.text_len = 0;
    if(phrase == story.speeches.size())
        state.active = false;
}


void tick_story(int ms)
{
    auto& state = ::story_state();
    auto const phrase = state.phrase;
    auto const& story = ::story(state.story);
    auto const& speech = story.speeches[phrase];
    auto const& text = speech.text;

    state.text_len += state.speed * ms / 1000.0f;

    size_t length = mb_strlen(text);
    if(state.text_len >= length) {
        state.text_len = length + 0.2f;

        float const& limit =
            ignore_text_mode_activation_speed;
        if(initial_text_speed > limit) {
            progress_story();
        }
    }
}

