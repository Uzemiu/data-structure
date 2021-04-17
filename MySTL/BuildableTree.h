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

