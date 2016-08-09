#include "json.h"
#include "utils.h"
#include <stack>
#include <typeinfo>
#include <iostream>

using std::stack;
namespace json{

Json::Json():root_(NULL){

}

Json::Json(JsonDataPtr data = NULL):root_(data){

}

Json::~Json(){
    delete root_;
}

Value Json::root(){
    Value value;
    value.setData(root_);
    return value;
}

void Json::setRoot(const Value& root){
    if(root_){
        delete root_;
    }
    root_ = root.data_;
}

void addData(JsonDataPtr parent, JsonDataPtr data, string key){
    if(typeid(*(parent)) == typeid(ObjectData)){
        ObjectData* oData = dynamic_cast<ObjectData*>(parent);
        oData->addItem(key, data);
    }else if(typeid(*(parent)) == typeid(ArrayData)){
        ArrayData* aData = dynamic_cast<ArrayData*>(parent);
        aData->addItem(data);
    }
}

bool inArrayLoop(JsonDataPtr parent){
    if(typeid(*(parent)) == typeid(ArrayData)){
        return true;
    }else{
        return false;
    }
}

const int EXCEPT_KEY  = 0;
const int EXCEPT_VALUE = 1;
void Json::parse(const string& jsonStr){
    stack<JsonDataPtr> dataStack;
    // root_ = new ObjectData();
    string key = "first";
    //  dataStack.push(root_);

    size_t len = jsonStr.length();
    size_t pos = 0;
    JsonDataPtr data = NULL;
    int exceptValue = EXCEPT_KEY;

    while(len > pos){
        if( jsonStr[pos] == ' ' || jsonStr[pos] == '\n' ||  jsonStr[pos] == '\t'){
            pos++;
            continue;
        }
        if(!dataStack.empty() && inArrayLoop(dataStack.top())){
            exceptValue = EXCEPT_VALUE;
        }

        switch(jsonStr[pos]){
        default:
            if(isDigitChar(jsonStr[pos])){
                assert(exceptValue == EXCEPT_VALUE);
                int start = pos;
                int end = start;
                while(isDigitChar(jsonStr[end])){
                    end++;
                }
                string val = jsonStr.substr(start, end - start);
                data = new NumberData(string2int(val));
                addData(dataStack.top(), data, key);
                exceptValue = EXCEPT_KEY;
                pos = end - 1;
            }
            break;

        case 't':
            assert(!dataStack.empty());
            assert(jsonStr.substr(pos, 4) == "true");
            assert(exceptValue == EXCEPT_VALUE);
            data = new BoolData(true);
            addData(dataStack.top(), data, key);
            exceptValue = EXCEPT_KEY;
            pos = pos + 3;
            break;

        case 'f':
            assert(!dataStack.empty());
            assert(jsonStr.substr(pos, 5) == "false");
            assert(exceptValue == EXCEPT_VALUE);
            data = new BoolData(false);
            addData(dataStack.top(), data, key);
            exceptValue = EXCEPT_KEY;
            pos = pos + 4;
            break;
        case '[':
        case '{':
        {
            if(jsonStr[pos] == '['){
                data = new ArrayData();
            }else{
                data = new ObjectData();
                exceptValue = EXCEPT_KEY;
            }

            if(!root_){
                dataStack.push(data);
                root_ = data;
            }else{
                addData(dataStack.top(), data, key);
                dataStack.push(data);
            }
            break;
        }case '}':
            assert(!dataStack.empty());
            assert(typeid(*(dataStack.top())) == typeid(ObjectData));
            dataStack.pop();
            break;

        case ']':
            assert(!dataStack.empty());
            assert(typeid(*(dataStack.top())) == typeid(ArrayData));
            dataStack.pop();
            break;
        case '\"':
            size_t pos2 = jsonStr.find('\"', pos + 1);
            assert(pos2 != std::string::npos);
            if(exceptValue == EXCEPT_KEY){
                key = jsonStr.substr(pos + 1, pos2 - (pos + 1));

                pos2 = jsonStr.find(':', pos2 - 1);
                assert(pos2 != std::string::npos);
                exceptValue = EXCEPT_VALUE;
            }else if(exceptValue == EXCEPT_VALUE){
                assert(!dataStack.empty());
                string value =  jsonStr.substr(pos + 1, pos2 - (pos + 1));

                data = new StringData(value);
                addData(dataStack.top(), data, key);
                exceptValue = EXCEPT_KEY;
            }
            pos = pos2;
            break;
        }

        pos++;

    }
    //ObjectData* oData = dynamic_cast<ObjectData*>(root_);
    //root_ = oData->getDataPtr("first");
}

string Json::toString(){
    return root_->toString();
}


}
