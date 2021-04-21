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

template<class T>
bool AVL<T>::insert(const T& ele) {
	Node<T>* tmp = insert(root, ele);
	if (tmp) {
		root = tmp;
		return true;
	}
	return false;
}

template<class T>
bool AVL<T>::remove(const T& ele) {
	Node<T>* tmp = remove(root, ele);
	if (tmp) {
		_size--;
		root = tmp;
		return true;
	}
	return false;
}

template<class T>
AVL<T>::Node<T>* AVL<T>::insert(TreeNode<T>* node, const T& ele) {
	if (!node)
		return new Node<T>(ele);
	if (ele < node->ele)
		node->left = insert(node->left, ele);
	else if (ele > node->ele)
		node->right = insert(node->right, ele);
	else
		return NULL;
	return balance(node);
}

template<class T>
AVL<T>::Node<T>* AVL<T>::balance(TreeNode<T>* _node) {
	if (!_node)
		return nullptr;
	Node<T>* node = (Node<T>*)_node;
	// 左树高大于右树
	if (get_height(node->left) - get_height(node->right) > ALLOW_BALANCE)
		if (get_height(node->left->left) >= get_height(node->left->right))
			node = rotate_right(node); //外侧子树高，单旋转
		else
			node = double_rotate_with_left_child(node); //内侧子树高，双旋转
	//对称情况
	else if (get_height(node->right) - get_height(node->left) > ALLOW_BALANCE)
		if (get_height(node->right->right) >= get_height(node->right->left))
			node = rotate_left(node); //外侧子树高，单旋转
		else
			node = double_rotate_with_right_child(node); //内侧子树高，双旋转
	node->height = max(get_height(node->left), get_height(node->right)) + 1;
	return node;
}

//左子树高的右旋转
template<class T>
AVL<T>::Node<T>* AVL<T>::rotate_right(TreeNode<T>* _k2) {
	Node<T>* k2 = (Node<T>*)_k2;
	Node<T>* k1 = (Node<T>*)k2->left;
	k2->left = k1->right;
	k1->right = k2;
	k2->height = max(get_height(k2->left), get_height(k2->right)) + 1;
	k1->height = max(get_height(k1->left), get_height(k1->right)) + 1;
	return k1;
}

//左子树高的双旋转
template<class T>
AVL<T>::Node<T>* AVL<T>::double_rotate_with_left_child(TreeNode<T>* k3) {
	k3->left = rotate_left(k3->left);
	return rotate_right(k3);
}

//右子树高的左旋转
template<class T>
AVL<T>::Node<T>* AVL<T>::rotate_left(TreeNode<T>* _k2) {
	Node<T>* k2 = (Node<T>*)_k2;
	Node<T>* k1 = (Node<T>*)k2->right;
	k2->right = k1->left;
	k1->left = k2;
	k2->height = max(get_height(k2->left), get_height(k2->right)) + 1;
	k1->height = max(get_height(k1->left), get_height(k1->right)) + 1;
	return k1;
}

//右子树高的双旋转
template<class T>
AVL<T>::Node<T>* AVL<T>::double_rotate_with_right_child(TreeNode<T>* k3) {
	k3->right = rotate_right(k3->right);
	return rotate_left(k3);
}

template<class T>
AVL<T>::Node<T>* AVL<T>::remove(TreeNode<T>* node, const T& ele) {
	if (!node) {
		return NULL;
	} else if (node->ele > ele) {
		node->left = remove(node->left, ele);
	} else if (node->ele < ele) {
		node->right = remove(node->right, ele);
	} else if (node->left && node->right) {
		// 相等并且有两棵子树
		TreeNode<T>* tmp = node->right;
		while (tmp->left) tmp = tmp->left; // findMin
		node->ele = tmp->ele;
		node->right = remove(node->right, node->ele);
	} else {
		// 只有一颗子树
		TreeNode<T>* origin = node;
		node = (node->left ? node->left : node->right);
		delete origin;
	}
	return balance(node);
}

template<class T>
int AVL<T>::get_height(TreeNode<T>* node) {
	return node ? ((Node<T>*)node)->height : -1;
}

