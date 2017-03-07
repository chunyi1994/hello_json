#ifndef JSON_STR
#define JSON_STR
#include "json_base.h"
#include "string"
#include "utils.h"
namespace json {

//json类型的字符串类型
class JsonStr : public JsonBase {
public:
    typedef JsonStr* Pointer;
public:
    JsonStr(std::string value) : value_(std::move(value)) {}

    virtual ~JsonStr() {// std::cout<<"~str"<<std::endl;
    }

    std::string get_value() const { return value_; }

    void set_value(std::string value) { value_ = std::move(value); }

    virtual std::string to_string() { return std::string("\"") + value_ + "\""; }

    static JsonStr* create(std::string value) { return new JsonStr(std::move(value)); }

private:
    std::string value_;
};

}//namespace
#endif // JSON_STR

