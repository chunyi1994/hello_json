# hello json


<p>你好json， 这是我在学习json语法的时候，顺带写的json解析器。还不完善，目前不支持utf8的转义。不支持科学技术法</p>

# 用法

```
{"arrkey":[1, "nihao", true, 1.234, 5, 6, 7, 7], 
  "boolkey":true, 
  "numkey":323, 
  "objectkey":{"subobject1":234, "subobject2":"234"}, 
  "strkey":"string!!!"}
```

<p>用c++编写生成这json字符串，只需要</p>


```
 Json::Pointer root = make_json({ { Key("arrkey"), {1, "nihao" , true, 1.234, 5, 6, 7, 7}}，
                                   { Key("boolkey"), true },
                                   { Key("numkey"), 323 },                               
                                   { Key("objectkey"), { {Key("subobject1"), 234}, 
                                                         {Key("subobjectZ"), "234"} } },
                                   { Key("strkey"), "string!!!" },
                               });
std::string jsonstr = root->to_string();
```

更多 https://github.com/sunfishgao/hello_json/blob/master/src/main.cpp

# 特色

<li>shared_ptr管理，自动释放 </li>

<li> 生成json格式方便</li>
