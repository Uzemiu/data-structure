#include "BinaryTree.h"

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
void BinaryTree<T>::insert(const T &ele) {
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
	return log2(_size) + 1;
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
void BinaryTree<T>::copy(TreeNode<T>* src, TreeNode<T>* &dest) {
	if (src) {
		dest = new TreeNode<T>(src->ele);
		copy(src->left, dest->left);
		copy(src->right, dest->right);
	}
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
