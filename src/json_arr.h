#ifndef JSON_ARR
#define JSON_ARR
#include "json_base.h"
#include "string"
#include "utils.h"
#include <vector>
#include <utility>
namespace json {

//json类型的数组类型
class JsonArr : public JsonBase {
public:
    typedef std::vector<JsonBase::Pointer> ValueVector;
    typedef JsonArr* Pointer;

public:
    JsonArr(ValueVector vec) : values_(std::move(vec)) {}

    JsonArr() : values_() {}

    virtual ~JsonArr() {
        for (auto pointer : values_) {
            delete pointer;
        }
    }

    JsonBase::Pointer at(std::size_t n) { return values_[n];}

    std::size_t size() const { return values_.size(); }

    static Pointer create(ValueVector vec) { return new JsonArr(std::move(vec)); }

    static Pointer create() { return new JsonArr(); }

    void add_item( JsonBase::Pointer value) { values_.push_back(value); }

    //ValueVector& get_vector() { return values_; }

    virtual std::string to_string() {
        std::string ret = "[";
        for(std::size_t i = 0; i < values_.size(); ++i){
            ret = ret + values_[i]->to_string() + ", ";
        }
        if (!values_.empty()) {
            ret.erase(ret.size() - 2, 2);
        }
        ret = ret + "]";
        return ret;
    }

private:
    std::vector<JsonBase::Pointer> values_;
};


}//namespace
#endif // JSON_ARR

