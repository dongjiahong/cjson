#ifndef __VALUE_H__
#define __VALUE_H__

using namespace std;

namespace json {

enum ValueType {
	nullValue = 0,
	intValue,
	uintValue,
	doubleValue,
	stringValue,
	booleanValue,
	arrayValue,
	objectValue
};


// class Value is object of json
class Value {
};

}	// namespace json

#endif
