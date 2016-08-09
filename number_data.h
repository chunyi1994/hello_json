#ifndef NUMBER_DATA
#define NUMBER_DATA
#include "json_base_data.h"
namespace json{

class NumberData : public JsonData{
public:
    NumberData(int data): data_(data){}

    NumberData():data_(0){}

    virtual ~NumberData(){}

    virtual string toString() {
        return int2string(data_);
    }
private:
    int data_;
};
}
#endif // NUMBER_DATA

