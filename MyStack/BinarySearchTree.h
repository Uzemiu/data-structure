#pragma once
#include "BinaryTree.h"

template <class T>
class BinarySearchTree : public BinaryTree<T> {

public:
	bool insert(const T &ele);
	bool remove(const T &ele);
	bool exists(const T &ele);

protected:
	template<class T>
	using Node = TreeNode<T>;
	using BinaryTree<T>::root;
	using BinaryTree<T>::_size;

private:
	bool insert(Node<T>* &node, const T& ele);
	bool remove(Node<T>* &node, const T& ele);
	bool remove_node(Node<T>*& node);
	bool exists(Node<T>* node, const T& ele);
};

