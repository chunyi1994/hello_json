# cppjson

# usage
```
{"arrkey":[1, "nihao", true, 1.234, 5, 6, 7, 7], 
  "boolkey":true, 
  "numkey":323, 
  "objectkey":{"subobject1":234, "subobject2":"234"}, 
  "strkey":"string!!!"}
```
<p>想要将以上json语句转换成c++的数据结构，只需要</p>

```
 Json::Pointer root = make_json({ { Key("strkey"), "string!!!" },
                                       { Key("numkey"), 323 },
                                       { Key("boolkey"), true },
                                       { Key("objectkey"), { {Key("subobject1"), 234},  {Key("subobject2"), "234"} } },
                                       { Key("arrkey"), {1, "nihao" , true, 1.234, 5, 6, 7, 7}}
                                   });


```
