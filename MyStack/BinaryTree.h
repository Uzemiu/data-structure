#pragma once
#include "LinkedStack.h"
#include <iostream>
#include <vector>
using namespace std;

template<class T>
class BinaryTree {
public:
	BinaryTree();
	BinaryTree(const BinaryTree<T> &original);
	BinaryTree<T>& operator=(const BinaryTree<T>& original);
	~BinaryTree();

	void insert(const T &ele);
	int size() const;
	bool empty() const;
	void clear();
	int height() const;

	template<class Fun>
	void pre_order_traverse(Fun apply);

	template<class Fun>
	void in_order_traverse(Fun apply);

	template<class Fun>
	void post_order_traverse(Fun apply);

	template<class Fun>
	void level_order_traverse(Fun apply);


protected:
	template<class T>
	struct Node {
		T ele;
		Node<T>* left;
		Node<T>* right;
		Node(T ele) : Node::Node(ele, NULL, NULL) {}
		Node(T ele, Node<T>* left, Node<T>* right) :ele(ele), left(left), right(right) {}
	};

	Node<T>* root;
	int _size;

private:
	void clear(Node<T>* node);
	void copy(Node<T>* src, Node<T>* &dest);
};

