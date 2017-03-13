#ifndef JSON_OBJ
#define JSON_OBJ

#include "json_base.h"
#include "string"
#include "utils.h"
#include <map>
#include <utility>
namespace json {

//json类型的object类型
class JsonObj : public JsonBase {
public:
    typedef std::map<std::string, JsonBase::Pointer> JsonObjMap;
    //typedef JsonObj* Pointer;
public:
    JsonObj(JsonObjMap map) : values_(std::move(map)) {}

    JsonObj() : values_() {}

    virtual ~JsonObj() {
    }

    std::size_t size() const { return values_.size(); }

    bool find(const std::string &key) { return values_.find(key) != values_.end(); }

    JsonBase::Pointer get(const std::string &key) { return values_[key]; }

    void add_item(const std::string& key, JsonBase::Pointer value) { values_[key] = value; }

    static JsonBase::Pointer create(JsonObjMap map) { return std::make_shared<JsonObj>(std::move(map)); }

    static JsonBase::Pointer create() {  return std::make_shared<JsonObj>(); }

    virtual JsonBase::Pointer clone() const {
        JsonObjMap values;
        for (const auto& pair : values_) {
            JsonBase::Pointer p = pair.second;
            if (p) {
                values[pair.first] = p->clone();
            }
        }
        return create(std::move(values));
    }


    virtual std::string to_string() {
        std::string ret = "{";
        for(JsonObjMap::iterator iter = values_.begin(); iter != values_.end(); iter++){
            ret = ret + "\"" + iter->first + "\":" + iter->second->to_string() + ", ";
        }
        if (!values_.empty()) {
            ret.erase(ret.size() - 2, 2);
        }
        ret = ret + "}";
        return ret;
    }

private:
    JsonObjMap values_;
};

}//namespace

#endif // JSON_OBJ

