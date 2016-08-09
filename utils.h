#ifndef UTILS_H
#define UTILS_H
#include <string>
#include <sstream>
#include<iostream>
using std::cout;
using std::endl;
using std::string;
namespace json{
static void log(const string& msg){
    cout<<msg<<endl;
}

static int string2int(const std::string& s){
    if(s.length() == 0){
        return 0;
    }
    std::istringstream is(s);
    int ret = 0;
    is>>ret;
    return ret;
}

static std::string int2string(int i){
    std::stringstream is;
    is<<i;
    return is.str();
}

static bool isDigit(const std::string &str){
    if(str.length() == 0){
        return false;
    }
    if('0' > str[0] || '9'< str[0]){
        if(str[0] != '+' && str[0] != '-'){
            return false;
        }
    }
    for(size_t i = 1; i < str.length(); i++){
        if('0' <=str[i] && str[i] <= '9'){
            continue;
        }else{
            return false;
        }
    }

    return true;
}

static bool isDigitChar(const char c){
    if('0' <= c && c <= '9'){
        return true;
    }
    return false;
}

}
#endif // UTILS_H

