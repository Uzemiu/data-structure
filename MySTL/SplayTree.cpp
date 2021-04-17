#include "SplayTree.h"

template<class T>
void SplayTree<T>::splay(const T& target) {
	Node<T>* dummy = new Node<T>(target);
	Node<T>* current = root, * child,
		* last_small = dummy,
		* first_large = dummy;
	// seach for target
	while (current && current->ele != target) {
		if (target < current->ele) {
			child = current->left;
			if (!child || target == child->ele) {
				// zig
				link_right(current, first_large);
			} else if (target < child->ele) {
				// zig-zig
				rotate_right(current);
				link_right(current, first_large);
			} else {
				// zig-zag
				link_right(current, first_large);
				link_left(current, last_small);
			}
		} else {
			child = current->right;
			if (!child || target == child->ele) {
				// zag
				link_left(current, last_small);
			} else if (target > child->ele) {
				// zag-zag
				rotate_left(current);
				link_left(current, last_small);
			} else {
				// zag-zig
				link_left(current, last_small);
				link_right(current, first_large);
			}
		}
	}

	if (!current) {
		current = new Node<T>(target);
		last_small->right = first_large->left = NULL;
	} else {
		last_small->right = current->left;
		first_large->left = current->right;
	}
	root = current;
	root->right = dummy->left; // root of larger-key subtree
	root->left = dummy->right; // root of larger-key subtree
	delete dummy;
}

template<class T>
void SplayTree<T>::link_right(Node<T>*& current, Node<T>*& first_large) {
	first_large->left = current;
	first_large = current;
	current = current->left;
}

template<class T>
void SplayTree<T>::link_left(Node<T>*& current, Node<T>*& last_small) {
	last_small->right = current;
	last_small = current;
	current = current->right;
}

template<class T>
void SplayTree<T>::rotate_right(Node<T>*& current) {
	Node<T>* child = current->left;
	current->left = child->right;
	child->right = current;
	current = child;
}

template<class T>
void SplayTree<T>::rotate_left(Node<T>*& current) {
	Node<T>* child = current->right;
	current->right = child->left;
	child->left = current;
	current = child;
}
