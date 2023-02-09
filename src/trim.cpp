#include "trim.hpp"
using std::string;

static bool is_whitespace(char symbol)
{
    const string whitespace = " \t\r\n";

    for(char c : whitespace)
        if(c == symbol)
            return true;
    return false;
}


string rtrim(string const& input)
{
    std::size_t last = input.size() - 1;
    while(last > 0 && is_whitespace(input[last]))
        last--;
    return input.substr(0, last + 1);
}

string ltrim(string const& input)
{
    std::size_t i = 0;
    while(i < input.size() && is_whitespace(input[i]))
        i++;
    return input.substr(i, input.size() - i);
}

string trim(string const& input)
{
    std::size_t i = 0;
    std::size_t j = input.size();

    while(i < j && is_whitespace(input[i]))
        i++;
    while(i < j && is_whitespace(input[j - 1]))
        j--;

    return input.substr(i, j - i);
}

