#ifndef INCLUDE_MB_STRING_HPP
#define INCLUDE_MB_STRING_HPP

#include <string>

using std::size_t;


size_t mb_strlen(std::string const&);
std::string mb_substr(std::string const&,
                      size_t start, size_t len);


#endif // INCLUDE_MB_STRING_HPP
