#include "String.h"
#include "LinkedList.h"

#include <string.h>

using namespace std;

String::String() {
	this->String::String("");
}

String::~String() {
	delete[] entries;
}

String::String(const String& copy) {
	this->String::String(copy.c_str());
}

String::String(const char* copy) {
	_length = strlen(copy); 
	entries = new char[_length + 1];
	strcpy_s(entries, _length + 1, copy);
}

String::String(LinkedList<char>& copy) {
	_length = copy.size();
	copy.push_last('\0');
	entries = copy.to_array();
	copy.pop_last();
}

void String::operator=(const String& copy) {
	delete[] entries;
	this->String::String(copy.c_str());
}

char String::operator[](int i) {
	if (i < 0 || i >= _length) {
		throw "Index out of bound";
	}
	return entries[i];
}

const char* String::c_str() const {
	return (const char*)entries;
}

size_t String::length() {
	return _length;
}

bool String::operator==(const String& str) {
	return strcmp(c_str(), str.c_str()) == 0;
}

bool String::operator!=(const String& str) {
	return !(*this == str);
}

String String::operator+(const String& str) {
	String res;
	delete[] res.entries;
	int new_size = _length + str._length + 1;
	res._length = new_size - 1;
	res.entries = new char[new_size];
	strcpy_s(res.entries, _length + 1, entries);
	strcat_s(res.entries, new_size, str.c_str());
	return res;
}

String& String::operator+=(const String& str) {
	int new_size = _length + str._length + 1;
	char* tmp = new char[new_size];
	strcpy_s(tmp, _length + 1, entries);
	strcat_s(tmp, new_size, str.entries);
	delete[] entries;
	entries = tmp;
	_length = new_size - 1;
	return *this;
}
