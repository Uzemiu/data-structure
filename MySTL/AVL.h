#pragma once
#include "BinarySearchTree.h"
template<class T>
class AVL: public BinarySearchTree<T>{
public:
	bool insert(const T& ele);
	bool remove(const T& ele);

protected:
	template<class T>
	struct Node :public TreeNode<T>{
		int height;
		Node(T ele) : Node(ele, 0, NULL, NULL) {}
		Node(T ele, int height, TreeNode<T>* left, TreeNode<T>* right):
			TreeNode<T>::TreeNode(ele,left,right), height(height) {}
	};
	using BinaryTree<T>::root;
	using BinaryTree<T>::_size;

private:
	static const int ALLOW_BALANCE = 1;

	AVL<T>::Node<T>* insert(TreeNode<T>* node, const T& ele);
	AVL<T>::Node<T>* balance(TreeNode<T>* node);
	AVL<T>::Node<T>* rotate_right(TreeNode<T>* k2);
	AVL<T>::Node<T>* double_rotate_with_left_child(TreeNode<T>* k3);
	AVL<T>::Node<T>* rotate_left(TreeNode<T>* k2);
	AVL<T>::Node<T>* double_rotate_with_right_child(TreeNode<T>* k3);
	AVL<T>::Node<T>* remove(TreeNode<T>* node, const T& ele);
	int get_height(TreeNode<T>* node);
};
