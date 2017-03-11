#ifndef UTILS_H
#define UTILS_H
#include <sstream>
#include <string.h>
#include <ctype.h>
#include <vector>
#include <string>
namespace utils {


static std::vector<std::string> split(const std::string& str, char c) {
    std::string line;
    std::stringstream ss(str);
    std::vector<std::string> result;
    while (std::getline(ss, line, c)) {
        result.push_back(line);
    }
    return result;
}
//todo 可能有问题
static std::vector<std::string> split(const std::string& str, const std::string& s) { //s是分隔符
    std::vector<std::string> result;
    std::size_t left = 0;
    std::size_t right = 0;
    while ( (right = str.find(s, left))  != std::string::npos)  {
        result.push_back(str.substr(left, right));
        left = right + s.length();
    }
    if (left < str.length()) {
        result.push_back(str.substr(left, str.size() - left));
    }
    return result;
}

static std::string replace_all(const std::string& str, const std::string& old, const std::string& newstr) {
    auto vec = split(str, old);
    std::string result;
    result.reserve(str.length());
    for (auto &s : vec) {
        result += s;
        result += newstr;
    }
    if (str.substr(str.size() - old.size(), old.size()) != old) {
        result.erase(result.size() - newstr.size(), newstr.size());
    }
    return result;
}

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

