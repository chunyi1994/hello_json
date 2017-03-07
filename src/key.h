#ifndef KEY_H
#define KEY_H
#include <string>
#include <utility>
namespace json {

struct Key{
    Key(const char* name) : object_name(name) {}
    Key(std::string name) : object_name(std::move(name)) {}
    std::string object_name;
};

}
#endif // KEY_H

