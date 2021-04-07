#pragma once
class String {
public:
	String();
	~String();
	String(const String& copy);
	String(const char* copy);
	void operator=(const String& copy);
	char operator[](const String& str);
	const char* c_str() const;
	size_t length();

protected:
	char* entries;
	int _length;
};

