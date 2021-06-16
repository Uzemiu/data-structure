#if 1
#pragma once
#include <iostream>
#include <string>
#include <iomanip>
#include <random>
#include <ctime>

#include "LinkedList.h"
#include "OrderedList.h"
#include "LinkedStack.h"
#include "SortableList.h"
#include "AHashTable.h"
#include "CHashTable.h"
#include "BinaryTree.h"
#include "BinarySearchTree.h"
#include "RBTree.h"
#include "BuildableTree.h"
#include "AVL.h"
#include "SplayTree.h"
#include "BTree.h"
#include "Trie.h"
#include "String.h"
#include "Digraph.h"
#include "Algorithm.h"
#include "Joseph.cpp"
#include "Polynomial.h"
#include "Browser.h"

using namespace std;

class Test {
public:


	template<class T>
	void assert_ordered(SortableList<T>& list) {
		for (int i = 1; i < list.size(); i++) {
			if (list[i] < list[i - 1]) {
				cout << "List is not ordered" << endl;
				break;
			}
		}
	}

	void test_sortable_list() {
		int n = 50;
		random_device rd;
		mt19937 rng(rd());
		int* arr0 = new int[n];
		for (int i = 0; i < n; i++) arr0[i] = i;
		shuffle(arr0, arr0 + n, rng);

		SortableList<int> l1;
		for (int i = 0; i < n; i++) {
			l1.push_last(arr0[i]);
		}
		SortableList<int> l2 = l1, l3 = l1, l4 = l1, l5 = l1, l6 = l1;
		vector<string> strs = { "rat","mop","cat","map","car","cot","tar","rap" };
		SortableList<string> l7;
		for (int i = 0; i < strs.size(); i++) {
			l7.push_last(strs[i]);
		}

		cout << "The list is:" << endl;
		cout << l1 << endl;
		cout << endl;

		cout << "Insertion sort:" << endl;
		l1.insertion_sort();
		assert_ordered(l1);
		cout << l1 << endl;
		cout << endl;

		cout << "Selection sort:" << endl;
		l2.selection_sort();
		assert_ordered(l2);
		cout << l2 << endl;
		cout << endl;

		cout << "Shell sort:" << endl;
		l3.shell_sort();
		assert_ordered(l3);
		cout << l3 << endl;
		cout << endl;

		cout << "Merge sort:" << endl;
		l4.merge_sort();
		assert_ordered(l4);
		cout << l4 << endl;
		cout << endl;

		cout << "Quick sort:" << endl;
		l5.quick_sort();
		assert_ordered(l5);
		cout << l5 << endl;
		cout << endl;

		cout << "Heap sort:" << endl;
		l6.heap_sort();
		assert_ordered(l6);
		cout << l6 << endl;
		cout << endl;

		cout << "The string list is:" << endl;
		cout << l7 << endl;
		cout << endl;
		cout << "Radix sort:" << endl;
		l7.radix_sort();
		assert_ordered(l7);
		cout << l7 << endl;

		delete[] arr0;
	}

	void test_ordered_list() {
		vector<int> eles{ 7,9,4,1,6,2,0,3,5,10,8 };
		OrderedList<int> list;
		for (int i = 0; i < eles.size(); i++) {
			list.insert(eles[i]);
			cout << "insert(" << eles[i] << ")" << endl;
		}
		cout << list << endl;

		for (int i = 0; i < 5; i++) {
			list.replace(i, i + 10);
			cout << "replace(" << i << "," << (i + 10) << ")" << endl;
			cout << list << endl;
		}

	}

	void print(LinkedList<int>& list) {
		for (int i = 0; i < list.size(); i++) {
			cout << list[i] << " ";
		}
	}

	void test_linked_list() {
		LinkedList<int> list;
		for (int i = 0; i < 10; i++) {
			list.insert(i, i + 1);
		}
		cout << "After insert 10 elements:" << endl;
		print(list);
		cout << endl;

		cout << "list.insert(0, -1)" << endl
			<< "list.insert(5,-5)" << endl
			<< "list.insert(1,-2)" << endl;
		list.insert(0, -1);
		list.insert(5, -5);
		list.insert(1, -2);
		print(list);
		cout << endl;

		cout << "list.remove(2)" << endl;
		list.remove(2);
		print(list);
		cout << endl;

		cout << "list.remove(0)" << endl;
		list.remove(0);
		print(list);
		cout << endl;

		cout << "list.remove(2)" << endl;
		list.remove(2);
		print(list);
		cout << endl;

		cout << "list2(list)" << endl;
		LinkedList<int> list2(list);
		print(list2);
		cout << endl;

		cout << "list[i]*=2" << endl;
		for (int i = 0; i < list.size(); i++) {
			list[i] *= 2;
		}
		cout << "list3(list)" << endl;
		LinkedList<int> list3 = list;
		print(list3);
		cout << endl;
	}

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
		for (int i = 1; i <= 16; i++) {
			tree1.insert(i);
			cout << tree1.height() << endl;
		}
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
		vector<int> eles{ 4,2,1,3,6,5,7,16,15,18,17,14,19,13,20,12,11,10,9,8 };
		cout << "Insert: ";
		for (int i = 0; i < eles.size(); i++) {
			cout << eles[i] << ",";
		}
		cout << endl;
		AVL<int> tree;
		for (int i = 0; i < eles.size(); i++) {
			tree.insert(eles[i]);
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

		cout << endl << "Remove: 16" << endl;
		tree.remove(16);

		cout << "Preorder: " << endl;
		tree.pre_order_traverse([](int& ele) {cout << ele << ", "; });
		cout << endl;
		cout << "Inorder: " << endl;
		tree.in_order_traverse([](int& ele) {cout << ele << ", "; });
		cout << endl;
		cout << "Postorder: " << endl;
		tree.post_order_traverse([](int& ele) {cout << ele << ", "; });
		cout << endl;
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

	void test_rbtree() {
		RBTree<int> tree;
		vector<int> to = { 11,2,14,1,7,15,5,8,4 };
		vector<int> rmv = { 1,7 };
		for (int i = 0; i < to.size(); i++) {
			tree.insert(to[i]);
		}

		tree.remove(1);
		tree.remove(7);
		tree.remove(-1);
		tree.remove(11);

		int j = 4;
	}

	void test_graph() {
		Digraph<6> graph;
		graph.add(3, 2);
		graph.add(4, 2);
		graph.add(2, 1);
		graph.add(2, 5);
		graph.add(1, 3);

		LinkedList<int> res;
		bool no_circle = graph.topo_sort(res);

		Digraph<6> graph2;
		int c1[8][3]{
			{1,2,1},
			{1,3,4},
			{1,4,6},
			{2,4,2},
			{2,5,4},
			{3,4,1},
			{4,5,1},
			{5,3,6}
		};
		int c2[10][3]{
			{0,1,5},
			{0,2,3},
			{0,4,2},
			{1,3,6},
			{1,2,2},
			{2,1,1},
			{2,3,2},
			{4,1,6},
			{4,2,10},
			{4,3,4}
		};
		for (int i = 0; i < 8; i++) {
			graph2.add(c2[i][0], c2[i][1], c2[i][2]);
		}
		int dist[6];
		graph2.shortest_path(5, dist);

	}

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
		int j = 7;
	}

	void test_sort() {
		int n = 10'000;
		clock_t start, end;
		random_device rd;
		mt19937 rng(rd());
		int* arr0 = new int[n];
		for (int i = 0; i < n; i++) arr0[i] = i;

		shuffle(arr0, arr0 + n, rng);
		start = clock();
		Algorithm::quick_sort(arr0, n);
		end = clock();
		cout << "QuickSort: "
			<< (double)(end - start) / CLOCKS_PER_SEC
			<< "s" << endl;

		shuffle(arr0, arr0 + n, rng);
		start = clock();
		sort(arr0, arr0 + n);
		end = clock();
		cout << "SystemSort: "
			<< (double)(end - start) / CLOCKS_PER_SEC
			<< "s" << endl;

		/*int arr2[14]{ 1,5,10,2,6,76,84,9,62,22,57,8,2,0 };
		Algorithm::selection_sort(arr2, 14);

		int arr3[14]{ 1,5,10,2,6,76,84,9,62,22,57,8,2,0 };
		Algorithm::insert_sort(arr3, 14);

		int arr4[14]{ 1,5,10,2,6,76,84,9,62,22,57,8,2,0 };
		Algorithm::shell_sort(arr4, 14);*/

		shuffle(arr0, arr0 + n, rng);
		start = clock();
		Algorithm::merge_sort(arr0, n);
		end = clock();
		cout << "MergeSort: " 
			<< (double)(end - start) / CLOCKS_PER_SEC 
			<< "s" << endl;

		delete[] arr0;
	}

};

#endif