#pragma once
#include "BinarySearchTree.h"

// zig->���� zag->����
// zig-zig m������s����
// zig-zag m������l�������൱��AVL�������ߵ�˫��ת
// zig     s����
// zag     s����
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
