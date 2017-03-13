#include <iostream>
#include "json.h"
#include "json_factory.h"
#include "test/dotest.h"
using namespace json;
using namespace std;
using namespace test;
#include <utility>
void example1() {
    //创建一个json
    //这个Json::Pointer 是一个shared_ptr,
    //可以在引用计数为0的时候，释放空间
    Json::Pointer root = make_json({
                                       { Key("strkey"), "string!!!" },
                                       { Key("numkey"), 323 },
                                       { Key("boolkey"), true },
                                       { Key("objectkey"), { {Key("subobject1"), 234},  {Key("subobject2"), "234"} } },
                                       { Key("arrkey"), {1, "nihao" , true, 1.234, 5, 6, 7, 7}}
                                   });
    //解析成字符串
    std::string str = root->to_string();
    std::cout<<str<<std::endl;
    //将str再解析回去成为数据结构
    Json::Pointer jsonptr = JsonFactory::create(str);
    if (!jsonptr) {
        std::cout<<"JsonFactory create error"<<std::endl;
        return;
    }
    //获取key为strkey的Json数据
    //如果获取了一个没有的key，会返回nullptr
    Json::Pointer  strjson = jsonptr->get("strkey");
    if (!strjson) {
        std::cout<<"get error"<<std::endl;
        return;
    }
    //如果是字符串类型，可以直接得到字符串
    if (strjson->is_str()) {
        std::cout<<strjson->get_str()<<std::endl;
    }
    Json::Pointer arrjson = jsonptr->get("arrkey");
    if (!arrjson) {
        std::cout<<"get error"<<std::endl;
        return;
    }
    //遍历
    for (std::size_t i = 0; i < arrjson->size(); ++i) {
        Json::Pointer j = arrjson->get(i);
        std::cout<<j->to_string()<<" ";
    }

}

int main()
{
    //example1();
    do_test();
    std::cout<<"hello world"<<std::endl;
    return 0;
}














