#include "String.h"

#include <string.h>

using namespace std;

String::String(const char* copy) {
	_length = strlen(copy); 
	entries = new char[_length + 1];
	strcpy_s(entries, _length + 1, copy);
}
