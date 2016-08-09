#ifndef JSON_DATA
#define JSON_DATA
#include "json_base_data.h"
#include "bool_data.h"
#include "number_data.h"
#include "object_data.h"
#include "string_data.h"
#include "array_data.h"
#include <typeinfo>
namespace json{
enum JsonDataType{
    TYPE_BOOL,
    TYPE_OBJECT,
    TYPE_STRING,
    TYPE_NUMBER,
    TYPE_ARRAY,
};

class Value{
public:
    friend class Json;
    Value():data_(NULL){

    }

    void setData(JsonDataPtr data){
        data_ = data;
    }

    void addValue(Value value){
        assert(typeid(*data_) == typeid(ArrayData));
        ArrayData* data = dynamic_cast<ArrayData*>(data_);
        data->addItem(value.data_);
    }

    void addValue(const string& key, Value value){
        assert(typeid(*data_) == typeid(ObjectData));
        ObjectData* data  = dynamic_cast< ObjectData*>(data_);
        data->addItem(key, value.data_);
    }



    Value operator[](size_t n){
        assert(typeid(*data_) == typeid(ArrayData));
        ArrayData* data = dynamic_cast<ArrayData*>(data_);
        Value value;
        value.setData(data->at(n));
        return value;
    }

    Value operator[](string key){
        assert(typeid(*data_) == typeid(ObjectData));
        ObjectData* data  = dynamic_cast< ObjectData*>(data_);
        Value value;
        value.setData(data->get(key));
        return value;
    }

    string toString(){
        return data_->toString();
    }

private:
    JsonDataPtr data_;

};

static Value makeBoolValue(bool data){
    Value value;
    value.setData(new BoolData(data));
    return value;
}

static Value makeStringValue(string data){
    Value value;
    value.setData(new StringData(data));
    return value;
}

static Value makeArrayValue(){
    Value value;
    value.setData(new ArrayData());
    return value;
}

static Value makeObjectValue(){
    Value value;
    value.setData(new ObjectData());
    return value;
}

static Value makeNumberValue(int data){
    Value value;
    value.setData(new NumberData(data));
    return value;
}
}

#endif // JSON_DATA

