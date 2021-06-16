#pragma once
#include "BinarySearchTree.h"
#include "LinkedList.h"

template<class T>
class BuildableTree : public BinarySearchTree<T> {

public:
	bool build_tree(LinkedList<T>& supply);

protected:
	template<class T>
	using Node = TreeNode<T>;
	using BinaryTree<T>::root;

private:
	void build_insert(int count, const T& data, LinkedList<Node<T>*>& last_node);
	void connect_trees(LinkedList<Node<T>*>& last_node);
};


template<class T>
bool BuildableTree<T>::build_tree(LinkedList<T>& supply) {
	bool res = true;
	LinkedList<Node<T>*> last_nodes;
	last_nodes.push_last(NULL);

	int count = 0;
	for (T x, last_x; count < supply.size();) {
		x = supply.get(count);
		if (count > 0 && x <= last_x) {
			res = false;
			break;
		}
		build_insert(++count, x, last_nodes);
		last_x = x;
	}
	root = last_nodes.peek_last();
	connect_trees(last_nodes);
	return res;
}

template<class T>
void BuildableTree<T>::build_insert(int count, const T& data, LinkedList<Node<T>*>& last_nodes) {
	int level;
	for (level = 1; count % 2 == 0; level++) {
		count /= 2;
	}
	Node<T>* next_node = new Node<T>(data);
	next_node->left = last_nodes.get(level - 1);
	if (last_nodes.size() <= level) {
		last_nodes.push_last(next_node);
	} else {
		last_nodes.replace(level, next_node);
	}
	if (level + 1 < last_nodes.size()) {
		Node<T>*& parent = last_nodes.get(level + 1);
		if (!parent->right) parent->right = next_node;
	}
}

template<class T>
void BuildableTree<T>::connect_trees(LinkedList<Node<T>*>& last_node) {
	Node<T>* high, * low;
	for (int high_level = last_node.size() - 1; high_level > 2;) {
		high = last_node.get(high_level);
		if (high->right) {
			high_level--;
		} else {
			int low_level = high_level;
			do {
				low = last_node.get(--low_level);
			} while (low && low->ele < high->ele);
			high->right = low;
			high_level = low_level;
		}
	}
}
