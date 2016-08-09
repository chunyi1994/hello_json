#ifndef ARRAY_DATA_H
#define ARRAY_DATA_H
#include "json_base_data.h"
#include "utils.h"
namespace json{
class DeleteArrayData{
    public:
    void operator()(JsonDataPtr ptr){
        if(ptr){
            delete ptr;
        }
    }
};

class ArrayData : public JsonData{
public:
    typedef vector<JsonDataPtr>::iterator VecIterator;
    ArrayData():datas_(){}

    virtual ~ArrayData(){
       std::for_each(datas_.begin(), datas_.end(), DeleteArrayData());
    }

    virtual string toString(){
        string ret = "[";
        for(size_t i = 0; i < datas_.size(); i++){
            ret = ret + datas_[i]->toString() + ", ";
        }
        ret.erase(ret.size() - 2, 2);
        ret = ret + "]";
        return ret;
    }

     JsonDataPtr at(size_t n){
        assert(n < datas_.size());
        return datas_[n];
    }

    void addItem(JsonDataPtr data){
        datas_.push_back(data);
    }

private:
    vector<JsonDataPtr> datas_;
};

}
#endif // ARRAY_DATA_H

