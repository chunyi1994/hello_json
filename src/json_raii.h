#ifndef JSON_ROOT
#define JSON_ROOT
#include "json.h"
#include <memory>
namespace json {

class JsonRaii : public Json {
public:
    JsonRaii() : Json() {}
    JsonRaii(double value) : Json(value) {}
    JsonRaii(float value) : Json(value) {}
    JsonRaii(int value) : Json(value) {}
    //JsonRaii(const JsonRaii& other) {}
    JsonRaii(const char* value) : Json(value) {}
    JsonRaii(std::string value) : Json(value) {}
    JsonRaii(const JsonRaii& other) : Json(other) {}
    JsonRaii(const Json& json) : Json(json) {}
    JsonRaii(bool value) : Json(value) {}
    JsonRaii(const std::initializer_list<Json>& list) : Json(list) {}
    JsonRaii(const std::initializer_list<std::pair<Key, Json>>& list) : Json(list) {}
    JsonRaii(JsonBase::Pointer root) : Json(root) {}
    virtual ~JsonRaii () { Json::destory(); }
    virtual Json::Pointer clone() const {
        Pointer new_json = std::make_shared<JsonRaii>();
        Json::do_clone(new_json);
        return new_json;
    }
private:
};

//class JsonRaii{
//public:
//    JsonRaii(Json json) : json_(json) {}
//    ~JsonRaii() { json_.destory(); }


//    //给数组用的，其他类型会返回自身
//    Json get (std::size_t n) { return json_.get(n); }

//    //给object用的，其他类型同上
//    Json get (const std::string& key) { return json_.get(key); }

//    //数组个数或者object成员个数
//    bool size() const { return json_.size();  }

//    //寻找object有无这个key，其他类型只会返回false
//    bool find(const std::string& key) const { return json_.find(key); }

//    //如果类型为number，返回int，其他类型调用无意义
//    int get_int() const { return json_.get_int(); }

//    //如果类型为字符串, 返回std::string，其他类型调用无意义
//    std::string get_str() const { return json_.get_str(); }

//    //如果是bool，返回bool， 其他类型调用无意义
//    bool get_bool() const { return json_.get_bool(); }

//    //将数据结构解析为Json格式的string
//    std::string to_string() const { return json_.to_string(); }

//private:
//    Json json_;
//};

}
#endif // JSON_ROOT

