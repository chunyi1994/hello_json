#ifndef JSON_FACTORY
#define JSON_FACTORY
#include <stack>
#include <string>
#include <assert.h>
#include "json.h"
#include <utility>
namespace json{


static void add_data(JsonBase::Pointer parent, JsonBase::Pointer data, std::string key){
    if(typeid(*(parent.get())) == typeid(JsonObj)){
        JsonObj* obj = dynamic_cast<JsonObj*>(parent.get());
        obj->add_item(key, data);
    }else if(typeid(*(parent.get())) == typeid(JsonArr)){
        JsonArr* arr = dynamic_cast< JsonArr*>(parent.get());
        arr->add_item(data);
    } else {
        //todo
    }
}

static bool is_in_array_loop(JsonBase::Pointer parent){
    if(typeid(*(parent)) == typeid(JsonArr)){
        return true;
    }else{
        return false;
    }
}

class JsonFactory {
public:
    //创建一个具有raii性质的json ptr
    static Json::Pointer create(std::string json_str) {
        return make_json(create_json(json_str));
    }

    //创建普通json
private:
    static Json create_json(std::string json_str) {
        const int EXCEPT_KEY  = 0;
        const int EXCEPT_VALUE = 1;
        std::stack<JsonBase::Pointer> data_stack;
        JsonBase::Pointer root = nullptr;
        std::string key = "";
        std::size_t len = json_str.length();
        std::size_t pos = 0;
        JsonBase::Pointer data = nullptr;
        int except_value = EXCEPT_KEY;

        while (len > pos) {
            if( json_str[pos] == ' ' || json_str[pos] == '\n' ||  json_str[pos] == '\t'){
                pos++;
                continue;
            }
            if(!data_stack.empty() && is_in_array_loop(data_stack.top())){
                except_value = EXCEPT_VALUE;
            }

            switch(json_str[pos]){
            default:
                if (utils::is_digit_char(json_str[pos])) {

                    assert(except_value == EXCEPT_VALUE);
                    if (except_value != EXCEPT_VALUE) {
                       // delete root;
                        return Json();
                    }
                    int start = pos;
                    int end = start;
                    while(utils::is_digit_char(json_str[end])){
                        end++;
                    }
                    std::string val = json_str.substr(start, end - start);
                    data = JsonNum::create(utils::to_double(val));
                    add_data(data_stack.top(), data, key);
                    if (is_in_array_loop(data_stack.top())) {
                       // except_value = EXCEPT_VALUE;
                    } else {
                        except_value = EXCEPT_KEY;
                    }
                    pos = end - 1;
                }
                break;
            case 't':
                assert(!data_stack.empty());
                assert(except_value == EXCEPT_VALUE);
                assert(utils::cmp_nocase(json_str.substr(pos, 4), "true"));
                if (data_stack.empty()
                     ||   except_value != EXCEPT_VALUE
                     ||  !utils::cmp_nocase(json_str.substr(pos, 4), "true")) {
                    //delete root;
                    return Json();
                }
                data = JsonBool::create(true);
                add_data(data_stack.top(), data, key);
                except_value = EXCEPT_KEY;
                pos = pos + 3;
                break;

            case 'f':
                assert(!data_stack.empty());
                assert(json_str.substr(pos, 5) == "false");
                assert(except_value == EXCEPT_VALUE);
                if (data_stack.empty()
                     ||   except_value != EXCEPT_VALUE
                     ||  !utils::cmp_nocase(json_str.substr(pos, 5), "false")) {
                   // delete root;
                    return Json();
                }
                data = JsonBool::create(false);
                add_data(data_stack.top(), data, key);
                except_value = EXCEPT_KEY;
                pos = pos + 4;
                break;
            case '[':
            case '{':
            {
                if(json_str[pos] == '['){
                    data = JsonArr::create();
                }else{
                    data = JsonObj::create();
                    except_value = EXCEPT_KEY;
                }

                if(!root){
                    data_stack.push(data);
                    root = data;
                }else{
                    add_data(data_stack.top(), data, key);
                    data_stack.push(data);
                }
                break;

            }case '}':
                assert(!data_stack.empty());
                assert(typeid(*(data_stack.top())) == typeid(JsonObj));
                if (data_stack.empty()
                     ||  typeid(*(data_stack.top())) != typeid(JsonObj)) {
                    //delete root;
                    return Json();
                }
                data_stack.pop();
                break;

            case ']':
                assert(!data_stack.empty());
                assert(typeid(*(data_stack.top())) == typeid(JsonArr));
                if (data_stack.empty()
                     ||  typeid(*(data_stack.top())) != typeid(JsonArr)) {
                    //delete root;
                    return Json();
                }
                data_stack.pop();
                if (!data_stack.empty() && !is_in_array_loop(data_stack.top())) {
                    except_value = EXCEPT_KEY;
                }
                break;
            case '\\':
                pos += 2;
                break;
            case '\"':
                size_t pos2 = pos;
                do {
                    pos2 = json_str.find('\"', pos2 + 1);
                } while (pos2 != std::string::npos && json_str[pos2 - 1] == '\\');

                assert(pos2 != std::string::npos);
                if (pos2 == std::string::npos) {
                    //delete root;
                    return Json();
                }
                if (except_value == EXCEPT_KEY){
                    key = json_str.substr(pos + 1, pos2 - (pos + 1));
                    pos2 = json_str.find(':', pos2 - 1);
                    if (pos2 == std::string::npos) {
                        //delete root;
                        return Json();
                    }
                    assert(pos2 != std::string::npos);
                    if (pos2 == std::string::npos) {
                        //delete root;
                        return Json();
                    }
                    except_value = EXCEPT_VALUE;
                } else if(except_value == EXCEPT_VALUE){
                    if (data_stack.empty()) {
                       // delete root;
                        return Json();
                    }
                    assert(!data_stack.empty());
                    if (data_stack.empty()) {
                        //delete root;
                        return Json();
                    }
                    std::string value =  json_str.substr(pos + 1, pos2 - (pos + 1));
                    data = JsonStr::create(std::move(value));
                    add_data(data_stack.top(), data, key);
                    except_value = EXCEPT_KEY;
                }
                pos = pos2;
                break;
            }
            pos++;
        }
        return Json(root);
    }
};
}
#endif // JSON_FACTORY

