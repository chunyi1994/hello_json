#include <iostream>
#include "json.h"
#include <fstream>
using namespace std;
using namespace json;

void example1();
void example2();
void example3();
int main()
{
 //example1();
    example2();

    return 0;
}


void example1(){
    Json json;
    //["name1", "name2", {"name3","value2", "bool" : true, "num" : 23345}]
    json.parse("[\"name1\",\"name2\",{\"name3\":\"value2\", \"num\":23345, \"bool\":    true  }]");
    Value data =  json.root();
    Value name1 = data[0];  //name1
    Value name2 = data[1];
    //data[2]是{"name3" : "value2", "num":23345, "bool": true }
    //data[2]["name3"] 是value2
    Value value2 = data[2]["name3"];
    cout<<name1.toString()<<endl;
    cout<<name2.toString()<<endl;
    cout<<value2.toString()<<endl;

    cout<<"#"<<endl;
}

void example2(){
    //["name1", "name2", {"bool" : false, "num" : 23345}]
    //所有的Value都应该由make*Value来生成,不同的类型不同的参数类型
    //ArrayValue可以用只有一个参数的addValue
    //objectValue 可以用两个参数的addValue
    Json json;
    Value arrayValue = makeArrayValue();
    Value stringValue1 = makeStringValue("name1");
    Value stringValue2 = makeStringValue("name2");

    Value objectValue = makeObjectValue();
    Value numValue = makeNumberValue(23345);
    Value boolValue = makeBoolValue(false);
    Value stringValue4 = makeStringValue("value2");
    objectValue.addValue("num", numValue);
    objectValue.addValue("bool", boolValue);
    objectValue.addValue("name3", stringValue4);


    arrayValue.addValue(stringValue1);
    arrayValue.addValue(stringValue2);
    arrayValue.addValue(objectValue);
    json.setRoot( arrayValue);

    cout<<json.toString()<<endl;
}

void example3(){
    std::fstream fs("1.txt");
    std::string content;
    std::string line;
    while(std::getline(fs, line)){
        content.append(line);
    }
     Json json;
     json.parse(content);
     cout<<json.toString()<<endl;
}

