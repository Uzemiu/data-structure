#pragma once
#include "BinarySearchTree.h"
template<class T>
class AVL: BinarySearchTree<T>{
public:
	bool insert(const T& ele);
	bool remove(const T& ele);
	int height() const;

protected:
	using BinaryTree<T>::Node;
	using BinaryTree<T>::root;
	using BinaryTree<T>::_size;

};

