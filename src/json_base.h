#ifndef JSONBASE
#define JSONBASE
#include <string>
#include <iostream>
namespace  json {

//json类型的基类
class JsonBase{
public:
    //typedef std::shared_ptr<JsonBase> Pointer;
    typedef JsonBase* Pointer;

    virtual std::string to_string() { return "JsonBase"; }

    virtual ~JsonBase(){}

    static Pointer create() { return new JsonBase(); }
};

} //namespace
#endif // JSONBASE

