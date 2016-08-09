#ifndef OBJECT_DATA
#define OBJECT_DATA
#include "json_base_data.h"
#include <utility>
namespace json{

class DeleteObjectData{
    public:
    void operator()(const std::pair<string, JsonDataPtr> & p){
        if(p.second){
            delete p.second;
        }
    }
};

class ObjectData : public JsonData{
public:
    typedef map<string, JsonDataPtr>::iterator MapIterator;

    ObjectData():datas_(){}

    virtual ~ObjectData(){
        std::for_each(datas_.begin(), datas_.end(), DeleteObjectData());
    }

    virtual string toString(){
        string ret = "{";
        for(MapIterator iter = datas_.begin(); iter != datas_.end(); iter++){
            ret = ret + "\"" + iter->first + "\" : " + iter->second->toString() + ", ";
        }
        ret.erase(ret.size() - 2, 2);
        ret = ret + "}";
        return ret;
    }

     JsonData* get(const string& key) {
        return datas_[key];
    }

    void addItem(string key, JsonDataPtr value){
        datas_.insert(std::make_pair(key, value));
    }
private:
    map<string, JsonDataPtr> datas_;
};

}
#endif // OBJECT_DATA

