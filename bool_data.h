#ifndef BOOL_DATA
#define BOOL_DATA
#include "json_base_data.h"
namespace json{

class BoolData : public JsonData{
public:
    BoolData():data_(false){}
    BoolData(bool data): data_(data){}
    virtual ~BoolData(){}
    virtual string toString(){
        if(data_){
            return "true";
        }
        return "false";
    }


private:
    bool data_;
};


}
#endif // BOOL_DATA

