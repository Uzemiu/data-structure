#pragma once
class String {
public:
	String();
	~String();
	String(const String& copy);
	String(const char* copy);
	void operator=(const String& copy);
	const char* c_str() const;


protected:
	char* entries;
	int length;
};

