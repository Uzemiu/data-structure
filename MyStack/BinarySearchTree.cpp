#include "BinarySearchTree.h"

template<class T>
bool BinarySearchTree<T>::insert(const T& ele) {
	return insert(root, ele);
}

template<class T>
bool BinarySearchTree<T>::remove(const T& ele) {
	if (remove(root, ele)) {
		_size--;
		return true;
	}
	return false;
}

template<class T>
bool BinarySearchTree<T>::exists(const T& ele) {
	return exists(root, ele);
}

template<class T>
int BinarySearchTree<T>::height() const {
	return 0;
}

template<class T>
bool BinarySearchTree<T>::insert(Node<T>* &node, const T& ele) {
	if (node) {
		if (node->ele == ele) {
			return false;
		} else if (node->ele > ele) {
			return insert(node->left, ele);
		} else {
			return insert(node->right, ele);
		}
	} else {
		node = new Node<T>(ele);
		return true;
	}
}

template<class T>
bool BinarySearchTree<T>::remove(Node<T>* &node, const T& ele) {
	if (!node || node->ele == ele) {
		return remove_node(node);
	} else if (node->ele > ele) {
		return remove(node->left, ele);
	} else {
		return remove(node->right, ele);
	}
}

template<class T>
bool BinarySearchTree<T>::remove_node(Node<T>*& node) {
	if (!node) {
		return false;
	}
	Node<T>* to_delete = node;
	if (!node->right) {
		node = node->left;
	} else if (!node->left) {
		node = node->right;
	} else {
		to_delete = node->left;
		Node<T>* parent = node;
		while (to_delete->right) {
			parent = to_delete;
			to_delete = to_delete->right;
		}
		node->ele = to_delete->ele;
		if (parent == node) node->left = to_delete->left;
		else parent->right = to_delete->left;
	}
	delete to_delete;
	return true;
}

template<class T>
bool BinarySearchTree<T>::exists(Node<T>* node, const T& ele) {
	if (!node) return false;
	if (node->ele > ele) return exists(node->left, ele);
	else if (node->ele < ele) return exists(node->right, ele);
	else return true;
}
