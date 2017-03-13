#ifndef JSON_NUM
#define JSON_NUM
#include "json_base.h"
#include <string>
#include "utils.h"
namespace json {

//json类型的数类型
class JsonNum : public JsonBase {
public:
   // typedef JsonNum* Pointer;
public:
    JsonNum(double value) : value_(value) {
    }


    virtual std::string to_string() { return utils::to_str(value_); }

    virtual ~JsonNum() {
        //std::cout<<"~num"<<std::endl;
    }

    void set_value(double value) { value_ = value;}

    double get_value() const { return value_; }

    static JsonBase::Pointer create(double value) { return std::make_shared<JsonNum>(value); }
    virtual JsonBase::Pointer clone() const {
       // std::cout<<"num clone:"<<value_<<std::endl;
        return create(value_);
    }

private:
    double value_;
};

}//namespace

#endif // JSON_NUM

