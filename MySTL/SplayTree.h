#pragma once
#include "BinarySearchTree.h"

// zig->向左 zag->向右
// zig-zig m右旋，s右旋
// zig-zag m左旋，l右旋，相当于AVL左子树高的双旋转
// zig     s右旋
// zag     s左旋
template<class T>
class SplayTree : public BinarySearchTree<T> {
public:
	void splay(const T& ele);

protected:
	template<class T>
	using Node = TreeNode<T>;
	using BinaryTree<T>::root;

private:
	void link_right(Node<T>*& current, Node<T>* &first_large);
	void link_left(Node<T>*& current, Node<T>* &last_small);
	void rotate_right(Node<T>*& current);
	void rotate_left(Node<T>*& current);
};
