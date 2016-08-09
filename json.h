#ifndef JSON_H
#define JSON_H
#include "json_value.h"
#include <vector>
#include <string>
using std::string;
using std::vector;
namespace json{
class Json
{
public:
    Json();
    Json(JsonDataPtr data);
    ~Json();
    void parse( const string& jsonStr);
    string toString();
    Value root();
    void setRoot(const Value& root);
private:
    JsonDataPtr root_;
};
}
#endif // JSON_H
