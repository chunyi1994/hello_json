#ifndef JSONBASE
#define JSONBASE
#include <string>
#include <iostream>
#include <memory>
namespace  json {

//json类型的基类
class JsonBase{
public:
    typedef std::shared_ptr<JsonBase> Pointer;
    //typedef JsonBase* Pointer;

    virtual std::string to_string() { return "JsonBase"; }

    virtual ~JsonBase(){}

   // static Pointer create() { return new JsonBase(); }
    static Pointer create() { return std::make_shared<JsonBase>(); }
    virtual Pointer clone() const { return create();  }
};

} //namespace
#endif // JSONBASE

