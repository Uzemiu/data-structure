#define _CRTDBG_MAP_ALLOC
//#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
#include <stdlib.h>
#include <crtdbg.h>

#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <algorithm>

#include <time.h>

//#include "Test.h";

#include "OrderedList.h"

using namespace std;


void test_ordered_list() {
	vector<int> eles{ 7,9,4,1,6,2,0,3,5,10,8 };
	OrderedList<int> list;
	for (int i = 0; i < eles.size(); i++) {
		list.insert(eles[i]);
		cout << "insert(" << eles[i] << ")" << endl;
		cout << list << endl;
	}

	for (int i = 0; i < 5; i++) {
		list.replace(i, i + 10);
		cout << "replace(" << i << "," << (i + 10) << ")" << endl;
		cout << list << endl;
	}

}

int main() {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	//Test test;
	//test.test_order();

	test_ordered_list();
	int z = 2;
	
	_CrtDumpMemoryLeaks();

	system("pause");
	return 0;
}

