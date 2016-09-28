#ifndef __READER_H__
#define __READER_H__

#include <string>
#include <stack>
#include "value.h"

using namespace std;
namespace json {

class Reader {
public:
	typedef const char* Location;
	typedef char Char;
	
	// Contructor of Reader
	Reader();

	bool parse(const string &docment);

	bool parse(const char *beginDoc,
			   const char *endDoc,
			   Value &root);

private:

	enum TokenType{
		tokenEndOfStream = 0,
		tokenObjectBegin,
		tokenObjectEnd,
		tokenArrayBegin,
		tokenArrayEnd,
		tokenString,
		tokenNumber,
		tokenTrue,
		tokenFalse,
		tokenNull,
		tokenArraySeparator,
		tokenMemberSeparator,
		tokenError
	};
	
	class Token {
	public:
		TokenType type_;
		Location start_;
		Location end_;
	};

	typedef stack<Value*> Nodes;
	Nodes nodes_;
	string docment_;
	Location begin_;
	Location end_;
	Location current_;
	Location lastValueEnd_;
	Value *lastValue_;

	void skipSpace();
	bool readValue();
	bool readToken(Token &token);
	Char getNextChar();
	bool match(Location pattern, int patternLength);

	bool readString();
	void readNumber();
	bool readObject(Token &tokenStart);
};
} // end json
#endif
