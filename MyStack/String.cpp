#include "String.h"

#include <string.h>

using namespace std;

String::String(const char* copy) {
	length = strlen(copy); 
	entries = new char[length + 1];
	strcpy_s(entries, length + 1, copy);
}
