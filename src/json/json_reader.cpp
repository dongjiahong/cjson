#include <iostream>

#include "../../include/reader.h"

using namespace std;
using namespace json;

static int stackDepth_g = 0;

// Contructor of Reader
Reader::Reader()
	: docment_(), begin_(), end_(), current_(),
	  lastValue_(), lastValueEnd_() {}

bool Reader::parse(const string &docment) {
	return true;
}

bool Reader::parse(const char *beginDoc, const char *endDoc, Value &root) {

	begin_ = beginDoc;
	end_ = endDoc;
	current_ = begin_;
	lastValueEnd_ = nullptr;
	lastValue_ = nullptr;

	while (!nodes_.empty()) {
		nodes_.pop();
	}
	nodes_.push(&root);

	stackDepth_g = 0;

	bool ok = readValue();
	return true;
}

void Reader::skipSpace() {
	while (current_ != end_) {
		Char c = *current_;
		if (c == ' ' || c == '\t' || c == '\r' || c == '\n') {
			++current_;
		} else {
			break;
		}
	}
}

bool Reader::readValue() {
	++stackDepth_g;
	Token token;
	bool successful = true;
	readToken(token);
	switch (token.type_) {
		case tokenObjectBegin:
			successful = readObject(token);
	}

}

bool Reader::readToken(Token &token) {
	skipSpace();
	token.start_ = current_;

	Char c = getNextChar();

	bool ok = true;
	switch(c) {
		case '{':
			token.type_ = tokenObjectBegin;
			break;
		case '}':
			token.type_ = tokenObjectEnd;
			break;
		case '[':
			token.type_ = tokenArrayBegin;
			break;
		case ']':
			token.type_ = tokenArrayEnd;
			break;
		case '"':
			token.type_ = tokenString;
			ok = readString();
			break;
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
		case '-':
			token.type_ = tokenNumber;
			readNumber();
			break;
		case 't':
			token.type_ = tokenTrue;
			ok = match("rue", 3);
			break;
		case 'f':
			token.type_ = tokenFalse;
			ok = match("alse", 4);
			break;
		case 'n':
			token.type_ = tokenNull;
			ok = match("ull", 3);
			break;
		case ',':
			token.type_ = tokenArraySeparator;
			break;
		case ':':
			token.type_ = tokenMemberSeparator;
			break;
		case 0:
			token.type_ = tokenEndOfStream;
			break;
		default:
			ok = false;
			break;
	}
	if (!ok) {
		token.type_ = tokenError;
	}
	token.end_ = current_;
	return true;
}

Reader::Char Reader::getNextChar() {
	if (current_ == end_) {
		return 0;
	}
	return *current_++;
}

bool Reader::match(Location pattern, int patternLength) {
	if (end_ - current_ < patternLength) {
		return false;
	}
	int index = patternLength;
	while (--index) {
		if (current_[index] != pattern[index]) {
			return false;
		}
	}
	current_ += patternLength;
	return true;
}

bool Reader::readString() {
	Char c = '\0';
	while (current_ != end_) {
		c = getNextChar();
		if (c == '"') {
			break;
		}
	}
	return c == '"';
}

void Reader::readNumber() {
	const char *p = current_;
	char c = '0';
	// integral part
	while (c >= '0' && c<='9') {
		c = (current_ = p) < end_ ? *p++ : '\0';
	}
	// fraction part
	if (c == '.') {
		c = (current_ = p) < end_ ? *p++ : '\0';
		while (c >= '0' && c <= '9') {
			c = (current_ = p) < end_ ? *p++ : '\0';
		}
	}
}

bool Reader::readObject(Token &tokenStart) {
	Token tokenName;
	string name;
	Value 
}
