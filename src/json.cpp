#include "json.h"
#include "json_type.h"
#include <iostream>
#include <assert.h>
#include "json_parser.h"
namespace json {

Json::Pointer make_json(Json json) {
    return std::make_shared<Json>(json);
}

Json::Pointer parse_json(const std::string& jsonstr) {
    Json json = create_json(jsonstr);
    if (json.null()) {
        return nullptr;
    } else {
        return make_json(json);
    }
}

Json::Json() : value_(nullptr) {
}

Json::Json(float value): value_(JsonNum::create(value)) {
}

Json::Json(double value) : value_(JsonNum::create(value)) {
}

Json::Json(int value): value_(JsonNum::create(static_cast<double>(value))) {
}

Json::Json(const Json &other) : value_(other.value_) {
}

Json::Json(const char *value) : value_(JsonStr::create(value)) {
}

Json::Json(std::string v)  : value_(JsonStr::create(v)) {
}

Json::Json(bool value): value_(JsonBool::create(value)) {
}

Json::Json(const std::initializer_list<Json> &list) {
    JsonArr::ValueVector values;
    for (auto& json : list) {
        values.push_back(json.value_);
    }
    value_ = JsonArr::create(values);
}

Json::Json(const std::initializer_list<std::pair<Key, Json> > &list) {
    JsonObj::JsonObjMap values;
    for (auto& pair : list) {
        values[pair.first.object_name] = pair.second.value_;
    }
    value_ = JsonObj::create(values);
}

Json::Json(JsonBase::Pointer root): value_(root)
{}

std::string Json::to_string() const {
    if (!null()) {
        return value_->to_string();
    } else {
        return "null";
    }
}

void Json::destory() {
    value_ = nullptr;
}

void Json::do_clone(Json::Pointer new_json) const {
    new_json->value_ = value_->clone();
}

Json::Pointer Json::clone() const {
    Pointer new_json = std::make_shared<Json>();
    do_clone(new_json);
    return new_json;
}

Json::Pointer Json::get(std::size_t n) {
    assert(!null());
    if (is_array()) {
        JsonArr* arr = dynamic_cast<JsonArr*>(value_.get());
        if (n < arr->size()) {
            return make_json(Json(arr->at(n)));
        }
    }
    return nullptr;
}
int Json::add_item(JsonBase::Pointer value) {
    assert(!null());
    if (is_array()) {
        JsonArr* arr = dynamic_cast<JsonArr*>(value_.get());
        arr->add_item(value);
        return 0;
    }
    return -1;
}

int Json::add_item(Json json) {
    return add_item(json.value_);
}

int Json::add_item(Json::Pointer json) {
    return add_item(json->value_);
}

Json::Pointer Json::get(const std::string &key) {
    assert(!null());
    if (is_object()) {
        JsonObj* obj = dynamic_cast<JsonObj*>(value_.get());
        if (obj->find(key)) {
            return make_json(Json(obj->get(key)));
        }
    }
    return nullptr;
}

//如果key存在，会覆盖
int Json::add_item(const std::string& key,JsonBase::Pointer value) {
    assert(!null());
    if (is_object()) {
        JsonObj* arr = dynamic_cast<JsonObj*>(value_.get());
        arr->add_item(key, value);
        return 0;
    }
    return -1;
}

int Json::add_item(const std::string &key, Json json) {
    return add_item(key, json.value_);
}

int Json::add_item(const std::string &key, Json::Pointer json) {
    return add_item(key, json->value_);
}

std::size_t Json::size() const {
    assert(!null());
    if (is_object()) {
        JsonObj* obj = dynamic_cast<JsonObj*>(value_.get());
        return obj->size();
    }
    if (is_array()) {
        JsonArr* arr = dynamic_cast<JsonArr*>(value_.get());
        return arr->size();
    }
    return 1;
}

bool Json::find(const std::string& key) const {
    assert(!null());
    if (is_object()) {
        JsonObj* obj = dynamic_cast<JsonObj*>(value_.get());
        return obj->find(key);
    }
    return false;
}

double Json::get_double() const {
    assert(!null());
    if (is_num()) {
        JsonNum* num = dynamic_cast<JsonNum*>(value_.get());
        return num->get_value();
    }
    return 0.0;
}

int Json::get_int() const {
    assert(!null());
    if (is_num()) {
        JsonNum* num = dynamic_cast<JsonNum*>(value_.get());
        return utils::to_int(num->get_value());
    }
    return 0;
}

bool Json::is_num() const {
    assert(!null());
    return typeid(*(value_.get())) == typeid(JsonNum);
}

bool Json::is_str() const {
    assert(!null());
    return typeid(*(value_.get())) == typeid(JsonStr);
}

bool Json::is_bool() const {
    assert(!null());
    return typeid(*(value_.get())) == typeid(JsonBool);
}

bool Json::is_array() const {
    assert(!null());
    return typeid(*(value_.get())) == typeid(JsonArr);
}

bool Json::is_object() const {
    assert(!null());
    return typeid(*(value_.get())) == typeid(JsonObj);
}

std::string Json::get_str() const {
    assert(!null());
    std::string result("");
    if (is_str()) {
        JsonStr* str = dynamic_cast<JsonStr*>(value_.get());
        return str->get_value();
    }
    return result;
}

bool Json::get_bool() const {
    assert(!null());
    if (is_bool()) {
        JsonBool* boolean = dynamic_cast<JsonBool*>(value_.get());
        return boolean->get_value();
    }
    return false;
}

bool Json::null() const {
    return !value_;
}





} //namespace

