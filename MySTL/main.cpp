#define _CRTDBG_MAP_ALLOC
//#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
#include <stdlib.h>
#include <crtdbg.h>

#include <iostream>
#include <string>
#include <iomanip>

#include "Test.h";

using namespace std;

void test_btree() {
	BTree<char, 5> bt;
	string str = "CNGAHEKQMFWLTZDPRXYS";
	for (int i = 0; i < str.length(); i++) {
		bt.insert(str[i]);
	}
	string str2 = "HTRE";
	for (int i = 0; i < str2.length(); i++) {
		bt.remove(str2[i]);
	}
	int j = 4;
}

int main() {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	Test test;
	//test.	
		test_btree();

	_CrtDumpMemoryLeaks();
	return 0;
}

