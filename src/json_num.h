#ifndef JSON_NUM
#define JSON_NUM
#include "json_base.h"
#include "string"
#include "utils.h"
namespace json {

//json类型的数类型
class JsonNum : public JsonBase {
public:
    typedef JsonNum* Pointer;
public:
    JsonNum(int value) : value_(value) {}

    virtual std::string to_string() { return utils::to_str(value_); }

    virtual ~JsonNum() { //std::cout<<"~num"<<std::endl;
    }

    void set_value(int value) { value_ = value;}

    int get_value() const { return value_; }

    static Pointer create(int value) { return new JsonNum(value); }

private:
    int value_;
};

}//namespace

#endif // JSON_NUM

