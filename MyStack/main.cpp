#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <stack>
#include <unordered_map>
#include "LinkedList.cpp"
#include "LinkedStack.cpp"
#include "SortableList.cpp"
#include "Joseph.cpp"
#include "Polynomial.h"
#include "Algorithm.h"

using namespace std;

int main() {
	SortableList<string> list;
	list.push("rat");
	list.push("mop");
	list.push("cat");
	list.push("map");
	list.push("car");
	list.push("top");
	list.push("cot");
	list.push("tar");
	list.push("rap");
	list.radix_sort();
	list.for_each([](string& str) {
		cout << str << endl;
				  });

	unordered_map<int, int> ma;
	string str = "123";
	std::hash<string> h;
	cout << h("123456789");
}

