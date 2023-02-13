#include "mb_string.hpp"
#include <stdexcept>

using std::string;


size_t mb_strlen(string const& text)
{
    size_t len = 0;
    for(char c : text)
        if((c & 0xc0) != 0x80)
            len++;

    return len;
}

std::string mb_substr(string const& text,
                      size_t start, size_t len)
{
    std::string msg = "mb_substr: request (" +
                      std::to_string(start) + ", " +
                      std::to_string(len) +
                      ") is out of range for '" +
                      text + "'";

    size_t first = 0;
    while(start > 0) {
        if((text[first] & 0xc0) != 0x80)
            start--;
        first++;
        if(first >= text.size())
            throw std::out_of_range(msg.c_str());
    }

    while((text[first] & 0xc0) == 0x80) {
        first++;
        if(first >= text.size())
            throw std::out_of_range(msg.c_str());
    }


    size_t end = first;

    while(len > 0) {
        if((text[end] & 0xc0) != 0x80)
            len--;
        end++;
        if(end == text.size())
            break;
    }
    if(len > 0)
        throw std::out_of_range(msg.c_str());

    while((text[end] & 0xc0) == 0x80) {
        end++;
        if(end == text.size())
            break;
    }

    return text.substr(first, end - first);
}

