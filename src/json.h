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
    Json();
    Json(int value);
    Json(const char* value);
    Json(std::string value);
    Json(bool value);
    Json(const std::initializer_list<Json>& list);

    //这里使用std::pair<Key, Json> 是为了适应c++的语法糖 {"key", "value"}
    //如果不引入Key类，会被识别成initializer_list<const char *>
    //引入key类变成{Key("key"), "value"}, 可以被识别成initializer_list<std::pair<Key, Json>
    Json(const std::initializer_list<std::pair<Key, Json>>& list);
    Json(JsonBase::Pointer root);
    //需要手动调用销毁
    void destory();

    //给数组用的，其他类型会返回自身
    Json operator[] (std::size_t n);

    //给object用的，其他类型同上
    Json operator[] (const std::string& key);

    //数组个数或者object成员个数
    bool size() const;

    //寻找object有无这个key，其他类型只会返回false
    bool find(const std::string& key) const;

    //如果类型为number，返回int，其他类型调用无意义
    int get_int() const;

    //如果类型为字符串, 返回std::string，其他类型调用无意义
    std::string get_str() const;

    //如果是bool，返回bool， 其他类型调用无意义
    bool get_bool() const;

    //将数据结构解析为Json格式的string
    std::string to_string() const;

     //调用destory()后，调用这个为true
    bool null() const;
private:
    JsonBase::Pointer value_;
private:

    //Json& operator=(const Json&) = delete;
};

}//namespace

#endif // JSON_H
