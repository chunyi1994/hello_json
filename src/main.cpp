#include <iostream>
#include "json.h"
#include "json_raii.h"
#include "json_factory.h"
#include "test/dotest.h"
using namespace json;
using namespace std;
using namespace test;
#include <utility>

void example1() {
    //{"arrkey":[1, 2, 3, 4, 5, 6, 7, 7],
    //  "boolkey":true,
    //  "numkey":323,
    //   "objectkey":   {
                  //"subobject1":234,
                 //"subobject2":"234"},
    //"strkey":"string"}

    Json json6 {
        { Key("strkey"), "string" },
        { Key("numkey"), 323 },
        { Key("boolkey"), true },
        { Key("objectkey"), { {Key("subobject1"), 234},
                                            {Key("subobject2"), "234"} }},
        {Key("arrkey"), {1,2,3,4,5,6,7,7}}
    };

    std::string str = json6.to_string();
     json6.destory();  //手动销毁
    std::cout<<str<<std::endl;

    auto json2 =  JsonFactory::create(str);
    JsonRaii jsonRaii(json2);  //析构时自动结束。
    str = json2.to_string();
    std::cout<<str<<std::endl;

}
int main()
{
     example1();
     do_test();
     std::cout<<"hello world"<<std::endl;
    return 0;
}














