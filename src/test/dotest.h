#include "test.h"
#include "../json.h"
#include "../json_factory.h"
#include "../utils.h"
using namespace json;
using namespace utils;
namespace test {

static void test1() {
    //创建一个json
    Json::Pointer root = make_json({
        { Key("strkey"), "string!!!" },
        { Key("numkey"), 323 },
        { Key("boolkey"), true },
        { Key("objectkey"), { {Key("subobject1"), 234},
                                            {Key("subobject2"), "234"} }},
        {Key("arrkey"), {1, "nihao" , true, 4, 5, 6, 7, 7}}
    });
    //解析成字符串
    std::string str = root->to_string();

    //将str再解析回去成为数据结构
     Json::Pointer jsonptr = JsonFactory::create(str);
    Json::Pointer  strjson = jsonptr->get("strkey");
    EXCEPT_EQ("string!!!", strjson->get_str());
    Json::Pointer arrjson = jsonptr->get("arrkey");
    EXCEPT_EQ(8, arrjson->size());
    std::vector<std::string> vec {
        "1", "\"nihao\"", "true", "4", "5", "6","7", "7"
    };
    for (std::size_t i = 0; i < arrjson->size(); ++i) {
        Json::Pointer j = arrjson->get(i);
        EXCEPT_EQ(j->to_string(),  vec[i]);
    }
}

static void test2() {
    Json::Pointer root = make_json({
        { Key("strkey"), "string!!!" },
        { Key("numkey"), 323 },
        { Key("boolkey"), true },
        { Key("objectkey"), { {Key("subobject1"), 234},
                                            {Key("subobject2"), "234"} }},
        {Key("arrkey"), {1, "nihao" , true, 4, 5, 6, 7, 7}}
    });
    std::cout<<"-----------------------"<<std::endl;
    auto root2 = root->clone();
}

static void do_test() {
   //test1();
    test2();
}

}//namespace