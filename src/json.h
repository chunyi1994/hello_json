#ifndef JSON_H
#define JSON_H
#include <initializer_list>
#include <memory>
#include <utility>
#include <json_type.h>
#include <iostream>
#include <map>
#include "key.h"
#include "json_base.h"
namespace json {

class Json {
public:
    typedef std::shared_ptr<Json> Pointer;
public:
    Json();
    Json(double value);
    Json(float value);
    Json(int value);
    Json(const Json& other);
    Json(const char* value);
    Json(std::string value);
    Json(bool value);
    Json(const std::initializer_list<Json>& list);
    virtual ~Json() { destory(); }
    //这里使用std::pair<Key, Json> 是为了适应c++的语法糖 {"key", "value"}
    //如果不引入Key类，会被识别成initializer_list<const char *>
    //引入key类变成{Key("key"), "value"}, 可以被识别成initializer_list<std::pair<Key, Json>
    Json(const std::initializer_list<std::pair<Key, Json>>& list);
    Json(JsonBase::Pointer root);

    virtual Pointer clone() const;

    //数组个数或者object成员个数
    std::size_t size() const;

    //寻找object有无这个key，其他类型只会返回false
    bool find(const std::string& key) const;

    //如果类型为number，返回int，其他类型调用无意义
    double get_double() const;
    int get_int() const;
    bool is_num() const;

    //如果类型为字符串, 返回std::string，其他类型调用无意义
    std::string get_str() const;
    bool is_str() const;

    //如果是bool，返回bool， 其他类型调用无意义
    bool get_bool() const;
    bool is_bool() const;

    //给数组用的，其他类型调用返回nullptr
    Pointer get (std::size_t n);
    int add_item(Json json);
    int add_item(Json::Pointer json);
    bool is_array() const;

    //给object用的，其他类型nullptr
    Pointer get(const std::string& key);
    int add_item(const std::string& key, Json json);
    int add_item(const std::string& key, Json::Pointer json);

    bool is_object() const;

    //将数据结构解析为Json格式的string
    std::string to_string() const;

    //调用destory()后，调用这个为true
    bool null() const;
protected:
    void do_clone(Pointer new_json) const;
    void destory();
private:
    int add_item(JsonBase::Pointer value);
    int add_item(const std::string& key, JsonBase::Pointer value);


private:
    JsonBase::Pointer value_;

};


Json::Pointer make_json(Json json);
Json::Pointer parse_json(const std::string& jsonstr);

}//namespace

#endif // JSON_H
