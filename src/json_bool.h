#ifndef JSON_BOOL
#define JSON_BOOL
#include "json_base.h"
#include "string"
#include "utils.h"
namespace json {
//json类型的bool类型
class JsonBool : public JsonBase {
public:
    typedef JsonBool* Pointer;
public:
    JsonBool(bool value) : value_(value) {}

    virtual std::string to_string() { return value_? "true" : "false"; }

    virtual ~JsonBool() { //std::cout<<"~bool"<<std::endl;
    }

    void set_value(bool value) { value_ = value;}

    bool get_value() const { return value_; }

    static JsonBool* create(bool value) { return new JsonBool(value); }

private:
    bool value_;
};

} //namespace
#endif // JSON_BOOL

