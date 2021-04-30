#define _CRTDBG_MAP_ALLOC
//#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
#include <stdlib.h>
#include <crtdbg.h>

#include <iostream>
#include <string>
#include <iomanip>

#include "Test.h";

using namespace std;

int main() {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	
	Test test; test.test_sort();

	int z = 1;
	

	_CrtDumpMemoryLeaks();
	return 0;
}

