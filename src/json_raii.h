#ifndef JSON_ROOT
#define JSON_ROOT
#include "json.h"
namespace json {

class JsonRaii {
public:
    JsonRaii(Json json) : json_(json) {}
    ~JsonRaii() { json_.destory(); }
private:
    Json json_;
};

}
#endif // JSON_ROOT

