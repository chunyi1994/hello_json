#ifndef JSON_STR
#define JSON_STR
#include "json_base.h"
#include "string"
#include "utils.h"
namespace json {

//json类型的字符串类型
class JsonStr : public JsonBase {
public:
  //  typedef JsonStr* Pointer;
public:
    JsonStr(std::string value) : value_() {
        std::string result = value;
        result = utils::replace_all(result, "\"", "\\\"");
        result = utils::replace_all(result, "\t", "\\t");
        //result = utils::replace_all(result, "\s", "\\s");
        result = utils::replace_all(result, "\n", "\\n");
        result = utils::replace_all(result, "\r", "\\r");
        value_ = result;
    }

    virtual ~JsonStr() { std::cout<<"~str"<<std::endl;
    }

    std::string get_value() const {
        std::string result = value_;
        result = utils::replace_all(result, "\\\"", "\"");
        result = utils::replace_all(result, "\\t", "\t");
        result = utils::replace_all(result, "\\s", " ");
        result = utils::replace_all(result, "\\n", "\n");
        result = utils::replace_all(result, "\\r", "\r");
        return result;
    }

    void set_value(std::string value) { value_ = std::move(value); }

    virtual std::string to_string() { return std::string("\"") + value_ + "\""; }

    static JsonBase::Pointer create(std::string value) { return std::make_shared<JsonStr>(std::move(value)); }

    virtual JsonBase::Pointer clone() const {
        std::cout<<"str clone:"<<value_<<std::endl;
        return create(value_);
    }

private:
    std::string value_;
};

}//namespace
#endif // JSON_STR

