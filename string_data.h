#ifndef STRING_DATA_H
#define STRING_DATA_H
#include "json_base_data.h"
namespace json{

class StringData : public JsonData{
public:
    StringData():data_(){}

    StringData(const string& data) : data_(data){}

    virtual ~StringData(){
    }

    virtual string toString() {
        return "\"" + data_ +"\"";
    }

private:
    string data_;
};

}

#endif // STRING_DATA_H

