#pragma once
#include "LinkedList.h"
class String {
public:
	String();
	~String();
	String(const String& copy);
	String(const char* copy);
	String(LinkedList<char> &copy);
	void operator=(const String& copy);
	char operator[](int i);
	const char* c_str() const;
	size_t length();

	bool operator==(const String& str);
	bool operator!=(const String& str);
	String operator+(const String& str);
	String& operator+=(const String& str);

protected:
	char* entries;
	size_t _length;
};

