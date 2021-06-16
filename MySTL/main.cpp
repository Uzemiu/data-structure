#define _CRTDBG_MAP_ALLOC
//#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
#include <stdlib.h>
#include <crtdbg.h>

#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <random>

#include <time.h>

//#include "Test.h";

#include "AVL.h"

using namespace std;

void level_order() {
	BinaryTree<int> tree;
	for (int i = 0; i <= 9; i++) {
		tree.insert(i);
	}

	cout << "Preorder: " << endl;
	tree.pre_order_traverse([](int& ele) {cout << ele << ", "; });
	cout << endl;
	cout << "Inorder: " << endl;
	tree.in_order_traverse([](int& ele) {cout << ele << ", "; });
	cout << endl;
	cout << "Postorder: " << endl;
	tree.post_order_traverse([](int& ele) {cout << ele << ", "; });
	cout << endl;
	cout << "Levelorder: " << endl;
	tree.level_order_traverse([](int& ele) {cout << ele << ", "; });
	cout << endl;
}

int main() {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	//Test test;
	//test.test_sort();
	level_order();
	
	int z = 3;
	
	_CrtDumpMemoryLeaks();

	system("pause");
	return 0;
}

