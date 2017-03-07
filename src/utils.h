#ifndef UTILS_H
#define UTILS_H
#include <sstream>
#include <string.h>
#include <ctype.h>
namespace utils {

static bool cmp_nocase(const std::string& s, const std::string& s2) {
    std::string::const_iterator p = s.begin();
    std::string::const_iterator p2 = s2.begin();
    while (p!=s.end() && p2!=s2.end())  {
         if (toupper(*p)!=toupper(*p2)) {
             return false;
         }
         ++p;
         ++p2;
      }
     return s2.size() == s.size();
}

template <class T>
static std::string to_str(const T& value) {
    std::stringstream ss;
    ss << value;
    return ss.str();
}

template <class T>
static int to_int(const T& value) {
    int result = 0;
    std::stringstream ss;
    ss << value;
    ss >> result;
    return result;
}

static bool is_digit_char(const char c){
    if('0' <= c && c <= '9'){
        return true;
    }
    return false;
}

} //namespace

#endif // UTILS_H

