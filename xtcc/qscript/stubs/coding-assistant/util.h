#ifndef util_h
#define util_h

#include <boost/algorithm/string.hpp>
#include <string>

std::string trim(const std::string& str,
                 const std::string& whitespace = " \t");

#endif /* util_h */
