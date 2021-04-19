#if 1
#pragma once
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
#include "BuildableTree.h"
#include "AVL.cpp"
#include "SplayTree.h"
#include "BTree.cpp"
#include "Trie.h"
#include "String.h"
#include "Polynomial.h"
#include "Browser.h"
#include "Algorithm.h"

using namespace std;

class Test {
public:
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
		for (int i = 0; i < 100; i++)
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

	void test_buildable_tree() {
		LinkedList<int> list;
		for (int i = 1; i <= 21; i++) list.push_last(i);
		BuildableTree<int> bt;
		bt.build_tree(list);
		cout << "------------------------------" << endl;
		bt.pre_order_traverse([](int& ele) {
			cout << ele << endl;
							  });
		cout << "------------------------------" << endl;
		bt.in_order_traverse([](int& ele) {
			cout << ele << endl;
							 });
		cout << "------------------------------" << endl;
		bt.post_order_traverse([](int& ele) {
			cout << ele << endl;
							   });
	}

	void test_avl() {
		AVL<int> tree;
		tree.insert(4);
		tree.insert(2);
		tree.insert(1);
		tree.insert(3);
		tree.insert(6);
		tree.insert(5);
		tree.insert(7);
		tree.insert(16);
		tree.insert(15);
		tree.insert(14);
		tree.insert(13);
		tree.insert(12);
		tree.insert(11);
		tree.insert(10);
		tree.insert(9);
		tree.insert(8);

		tree.remove(4);
		tree.remove(6);
		cout << "------------------------------" << endl;
		tree.in_order_traverse([](int& ele) {
			cout << ele << endl;
							   });
	}


	void test_splay_tree() {
		SplayTree<int> st;
		st.insert(13);
		st.insert(5);
		st.insert(16);
		st.insert(3);
		st.insert(10);
		st.insert(14);
		st.insert(18);
		st.insert(2);
		st.insert(4);
		st.insert(8);
		st.insert(11);
		st.insert(15);
		st.insert(17);
		st.insert(20);
		st.insert(1);
		st.insert(7);
		st.insert(9);
		st.insert(12);
		st.insert(19);
		st.insert(6);

		st.splay(19);

		cout << "-------------------------" << endl;
		st.pre_order_traverse([](int& i) {
			cout << i << " ";
							  });
		cout << endl;
	}


	void test_trie() {
		Trie trie;
		trie.insert("a");
		trie.insert("aa");
		trie.insert("ab");
		trie.insert("ac");
		trie.insert("aba");
		trie.insert("abc");
		trie.insert("abba");
		trie.insert("abaca");

		trie.insert("baba");

		trie.insert("caaba");
		trie.insert("ca");
		trie.insert("c");
		trie.insert("ca");
		trie.insert("cab");
		trie.insert("caba");

		cout << trie.search("abaca") << endl
			<< trie.search("abac") << endl
			<< trie.search("bag") << endl;
	}
};

#endif