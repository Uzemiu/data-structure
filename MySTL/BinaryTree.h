#pragma once
#include "LinkedStack.h"
#include <iostream>
#include <vector>
using namespace std;

enum Color { RED, BLACK };

template<class T>
struct TreeNode {
	T ele;
	Color color;

	TreeNode<T>* left;
	TreeNode<T>* right;
	TreeNode(T ele) : TreeNode::TreeNode(ele, NULL, NULL) {}
	TreeNode(T ele, TreeNode<T>* left, TreeNode<T>* right) 
		:ele(ele), left(left), right(right) {}

	virtual Color get_color() { return RED; }
	virtual void set_color(Color color) {}
	virtual TreeNode<T>* get_parent() { return NULL; }
	virtual void set_parent() {}
};

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
	TreeNode<T>* root;
	int _size;

private:
	void clear(TreeNode<T>* node);
	void copy(TreeNode<T>* src, TreeNode<T>* &dest);
	int height(TreeNode<T>* node, int h) const;
};

template<class T>
BinaryTree<T>::BinaryTree() {
	root = NULL;
	_size = 0;
}

template<class T>
BinaryTree<T>::BinaryTree(const BinaryTree<T>& original) {
	copy(original.root, root);
}

template<class T>
BinaryTree<T>& BinaryTree<T>::operator=(const BinaryTree<T>& original) {
	clear();
	copy(original.root, root);
	return *this;
}

template<class T>
BinaryTree<T>::~BinaryTree() {
	clear();
}

template<class T>
void BinaryTree<T>::insert(const T& ele) {
	TreeNode<T>* n = new TreeNode<T>(ele);
	if (empty()) {
		root = n;
		_size++;
		return;
	}
	LinkedStack<bool> route; // 1 for left, 0 for right
	for (int s = _size; s > 0; s = (s - 1) / 2) {
		route.push(s & 1);
	}
	TreeNode<T>* node = root;
	while (route.size() > 1) {
		node = (route.pop() ? node->left : node->right);
	}
	if (route.peek()) {
		node->left = n;
	} else {
		node->right = n;
	}
	_size++;
}

template<class T>
int BinaryTree<T>::size() const {
	return _size;
}

template<class T>
bool BinaryTree<T>::empty() const {
	return root == NULL;
}

template<class T>
void BinaryTree<T>::clear() {
	clear(root);
	_size = 0;
	root = NULL;
}

template<class T>
int BinaryTree<T>::height() const {
	return height(root, 0);
}

template<class T>
void BinaryTree<T>::clear(TreeNode<T>* node) {
	if (node) {
		clear(node->left);
		clear(node->right);
		delete node;
	}
}

template<class T>
void BinaryTree<T>::copy(TreeNode<T>* src, TreeNode<T>*& dest) {
	if (src) {
		dest = new TreeNode<T>(src->ele);
		copy(src->left, dest->left);
		copy(src->right, dest->right);
	}
}

template<class T>
int BinaryTree<T>::height(TreeNode<T>* node, int h) const{
	return node 
		? max(height(node->left, h + 1), height(node->right, h + 1))
		: h;
}

template<class T>
template<class Fun>
void BinaryTree<T>::pre_order_traverse(Fun apply) {
	if (empty()) return;
	TreeNode<T>* node = root;
	LinkedStack<TreeNode<T>*> stack;
	stack.push(root);
	while (!stack.empty()) {
		node = stack.pop();
		apply(node->ele);
		if (node->right) stack.push(node->right);
		if (node->left) stack.push(node->left);
	}
}

template<class T>
template<class Fun>
void BinaryTree<T>::in_order_traverse(Fun apply) {
	if (empty()) return;
	TreeNode<T>* node = root;
	LinkedStack<TreeNode<T>*> stack;
	while (node || !stack.empty()) {
		while (node) {
			stack.push(node);
			node = node->left;
		}
		if (!stack.empty()) {
			node = stack.pop();
			apply(node->ele);
			node = node->right;
		}
	}
}

template<class T>
template<class Fun>
void BinaryTree<T>::post_order_traverse(Fun apply) {
	if (empty()) return;
	TreeNode<T>* node = root;
	LinkedStack<TreeNode<T>*> stack, path;
	while (node || !stack.empty()) {
		while (node) {
			stack.push(node);
			path.push(node);
			node = node->right;
		}
		if (!path.empty()) {
			node = path.pop();
			node = node->left;
			if (!node && path.empty()) break;
		}
	}
	while (!stack.empty()) {
		apply(stack.pop()->ele);
	}
}

template<class T>
template<class Fun>
void BinaryTree<T>::level_order_traverse(Fun apply) {
	if (empty()) return;
	LinkedList<TreeNode<T>*> queue;
	queue.push_last(root);
	while (!queue.empty()) {
		TreeNode<T>* node = queue.pop_first();
		apply(node->ele);
		if (node->left) queue.push_last(node->left);
		if (node->right) queue.push_last(node->right);
	}
}
