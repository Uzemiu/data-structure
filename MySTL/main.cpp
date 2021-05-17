#define _CRTDBG_MAP_ALLOC
//#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
#include <stdlib.h>
#include <crtdbg.h>

#include <iostream>
#include <string>
#include <iomanip>
#include <algorithm>

#include <time.h>

#include "Test.h";

using namespace std;

void test_rbtree() {
	RBTree<int> tree;
	vector<int> to = { 11,2,14,1,7,15,5,8, 4 };
	for (int i = 0; i < to.size(); i++) {
		tree.insert(to[i]);
	}
	int j = 6;
}

int main() {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	//Test test;
	//test.test_sort();

	test_rbtree();
	int z = 2;
	
	_CrtDumpMemoryLeaks();

	system("pause");
	return 0;
}

