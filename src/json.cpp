#include "json.h"
#include "json_type.h"
namespace json {

Json::Json() : value_(nullptr) {
}

Json::Json(int value) : value_(JsonNum::create(value)){
}

Json::Json(const char *value) : value_(JsonStr::create(value)) {
}

Json::Json(std::string value)  : value_(JsonStr::create(value)) {
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
    if (value_) {
        return value_->to_string();
    } else {
        return "null";
    }
}

void Json::destory() {
    delete value_;
    value_ = nullptr;
}

Json Json::operator[](std::size_t n) {
    if (typeid(*(value_)) == typeid(JsonArr)) {
        JsonArr::Pointer arr = dynamic_cast<JsonArr::Pointer>(value_);
        if (n < arr->size()) {
            return Json(arr->at(n));
        }
    }
    return *this;
}

Json Json::operator[](const std::string &key) {
    if (typeid(*(value_)) == typeid(JsonObj)) {
        JsonObj::Pointer obj = dynamic_cast<JsonObj::Pointer>(value_);
        if (obj->find(key)) {
            return Json(obj->get(key));
        }
    }
    return *this;
}

bool Json::size() const {
    if (!value_) {
        return 0;
    }
    if (typeid(*(value_)) == typeid(JsonObj)) {
        JsonObj::Pointer obj = dynamic_cast<JsonObj::Pointer>(value_);
        return obj->size();
    }
    if (typeid(*(value_)) == typeid(JsonArr)) {
        JsonArr::Pointer arr = dynamic_cast<JsonArr::Pointer>(value_);
        return arr->size();
    }
    return 1;
}

bool Json::find(const std::string& key) const {
    if (typeid(*(value_)) == typeid(JsonObj)) {
        JsonObj::Pointer obj = dynamic_cast<JsonObj::Pointer>(value_);
        return obj->find(key);
    }
    return false;
}

int Json::get_int() const {
    if (typeid(*(value_)) == typeid(JsonNum)) {
        JsonNum::Pointer num = dynamic_cast<JsonNum::Pointer>(value_);
        return num->get_value();
    }
    return 0;
}

std::string Json::get_str() const {
    if (typeid(*(value_)) == typeid(JsonStr)) {
        JsonStr::Pointer str = dynamic_cast<JsonStr::Pointer>(value_);
        return str->get_value();
    }
    return "";
}

bool Json::get_bool() const {
    if (typeid(*(value_)) == typeid(JsonBool)) {
        JsonBool::Pointer boolean = dynamic_cast<JsonBool::Pointer>(value_);
        return boolean->get_value();
    }
    return false;
}

bool Json::null() const {
    return bool(value_);
}

} //namespace

