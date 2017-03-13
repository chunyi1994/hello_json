#include "test.h"
#include "../json.h"
#include "../json_parser.h"
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
    Json::Pointer jsonptr = parse_json(str);
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
    //克隆了一份一模一样的
    EXCEPT_TRUE(!root->null());

    auto root2 = root->clone();
    EXCEPT_TRUE(!root2->null());

    Json::Pointer arrkey = root->get("arrkey");
    EXCEPT_TRUE(arrkey);
    EXCEPT_TRUE(arrkey->is_array());
    {
    Json::Pointer new_json = make_json({ 8,9,10, "wobuhao", false });
    EXCEPT_TRUE(!new_json->null());
    arrkey->add_item(new_json);
    }
    std::cout<<root->to_string()<<std::endl;
}

static void do_test() {
    test2();
    //test2();
}

}//namespace
