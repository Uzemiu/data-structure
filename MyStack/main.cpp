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
#include "AHashTable.cpp"
#include "CHashTable.cpp"
#include "String.h"
#include "Polynomial.h"
#include "Algorithm.h"

using namespace std;

void test_radix_sort() {
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
}

void test_hashtable_1() {
	AHashTable<int, int> ht;
	int V = 0;
	for (int i = 0; i < 97; i++) {
		ht.insert(i, i);
	}
	for (int i = 33; i < 66; i++) {
		ht.remove(i, V);
	}
	for (int i = 97; i < 97 * 2; i++) {
		ht.insert(i, -i);
	}
	for (int i = 0; i < 97 * 2; i++) {
		int num = 0;
		if (ht.get(i, num)) {
			cout << num << endl;
		}
	}
}

void test_string2() {
	String s1 = "asd123456789", s2 = "1231231235467897";
	//s1 += s2;
}

void test_string() {
	LinkedList<char> list;
	list.push('5');
	list.push('6');
	list.push('7');
	list.push('8');
	String s1 = "asd";
	String s2("123");
	String s3(s1);
	String s4(list); 
	String s5 = s1 + s2;
	for (int i = 0; i < 100; i++) {
		s5 = s5 + s1;
		//cout << s5.c_str() << endl;
	}
}

int main() {
	int i = 0;
	cin >> i;
	test_string2();
	int j = 0;
	cin >> i;
}

