#ifndef VALUE_DATA_H
#define VALUE_DATA_H
#include <string>
#include <map>
#include <unistd.h>
#include <assert.h>
#include <vector>
#include <algorithm>
#include "utils.h"
using std::map;
using std::string;
using std::vector;
namespace json{

class JsonData{
public:
    virtual string toString(){return "JsonData";}
    virtual ~JsonData(){}
};

typedef JsonData* JsonDataPtr;

}
#endif // VALUE_DATA_H

