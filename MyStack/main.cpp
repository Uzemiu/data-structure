#define _CRTDBG_MAP_ALLOC
//#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
#include <stdlib.h>
#include <crtdbg.h>

#include <iostream>
#include <string>
#include <iomanip>

#include "LinkedList.cpp"
#include "LinkedStack.cpp"
#include "SortableList.cpp"
#include "Joseph.cpp"
#include "AHashTable.cpp"
#include "CHashTable.cpp"
#include "BinaryTree.cpp"
#include "BinarySearchTree.cpp"
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

void test_hashtable_2() {
	int v;

	std::hash<int> h;
	vector<int> vec;
	for (int i = 0; i < 999; i++) {
		int num = h(i) % 97;
		if (num == 23) vec.push_back(i);
	}
	CHashTable<int, int> table;
	for (int i = 0; i < vec.size(); i++) {
		table.insert(vec[i], vec[i]);
	}
	for (int i = vec.size() / 2; i < vec.size(); i++) {
		table.remove(vec[i], v);
	}
	for (int i = 0; i < vec.size(); i++) {
		cout << vec[i] << " | ";
		if (table.get(vec[i], v)) {
			cout << v << endl;
		} else {
			cout << "Not Found" << endl;
		}
	}
}

void test_string2() {
	String s1 = "asd123456789", s2 = "1231231235467897";
	for(int i=0;i<100;i++)
		s1 += s2;
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

void test_binary_tree() {
	BinaryTree<int> tree1;
	for (int i = 1; i <= 10; i++) tree1.insert(i);
	BinaryTree<int> tree2(tree1);
	BinaryTree<int> tree = tree2;
	cout << "------------------------------" << endl;
	tree.pre_order_traverse([](int& ele) {
		cout << ele << endl;
							});
	cout << "------------------------------" << endl;
	tree.in_order_traverse([](int& ele) {
		cout << ele << endl;
						   });
	cout << "------------------------------" << endl;
	tree.post_order_traverse([](int& ele) {
		cout << ele << endl;
							 });
	
}

void test_bst() {
	BinarySearchTree<int> bst;

	bst.insert(5);
	bst.insert(3);
	bst.insert(8);
	bst.insert(2);
	bst.insert(4);
	bst.insert(7);
	bst.insert(9);
	bst.insert(1);

	bst.remove(5);
	bst.remove(3);


	cout << "------------------------------" << endl;
	bst.pre_order_traverse([](int& ele) {
		cout << ele << endl;
							});
	cout << "------------------------------" << endl;
	bst.in_order_traverse([](int& ele) {
		cout << ele << endl;
						   });
	cout << "------------------------------" << endl;
	bst.post_order_traverse([](int& ele) {
		cout << ele << endl;
							 });
}

int main() {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	test_bst();

	_CrtDumpMemoryLeaks();
	return 0;
}

