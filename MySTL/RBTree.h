#pragma once
#include "BinarySearchTree.h"

#include <iostream>

using namespace std;

enum RBStatus {DUPLICATED, SUCCESS, NODE_RED, RIGHT_RED, LEFT_RED};

template<class T>
class RBTree: BinarySearchTree<T> {
public:
	bool insert(const T& data);
	bool remove(const T& data);


protected:

	template<class T>
	struct Node: public TreeNode<T> {
		Node(T ele):Node(ele, RED) {}
		Node(T ele, Color color) : 
			TreeNode<T>::TreeNode(ele, NULL, NULL) {
			this->color = color;
		}
	};

	using BinaryTree<T>::root;
	using BinaryTree<T>::_size;

private:
	RBStatus insert(TreeNode<T>* &node, const T& data);

	RBStatus modify_left(TreeNode<T>* &node, RBStatus child_status);
	RBStatus modify_right(TreeNode<T>* &node, RBStatus child_status);

	RBStatus flip_color(TreeNode<T>* node);
	RBStatus flip_color_single(TreeNode<T>* node);

	RBStatus rotate_right(TreeNode<T>* &k2);
	RBStatus double_rotate_right(TreeNode<T>* &k3);
	RBStatus rotate_left(TreeNode<T>* &k2);
	RBStatus double_rotate_left(TreeNode<T>* &k3);
};

template<class T>
inline bool RBTree<T>::insert(const T& data) {
	Node<T>*& _root = (Node<T>*&)root;
	RBStatus status = insert(root, data);
	switch (status) {
	case NODE_RED:
		_root->color = BLACK;
	case SUCCESS:
		return true;
	case RIGHT_RED:
	case LEFT_RED:
		cout << "Error detected" << endl;
	default:
		// duplicated 
		return false;
	}
}

template<class T>
inline bool RBTree<T>::remove(const T& data) {
	return false;
}

template<class T>
inline RBStatus RBTree<T>::insert(TreeNode<T>* &node, const T& data) {
	if (node == NULL) {
		node = new Node<T>(data);
		return NODE_RED;
	} else if(data == node->ele){
		return DUPLICATED;
	} else if (data < node->ele) {
		RBStatus child_status = insert(node->left, data);
		return modify_left(node, child_status);
	} else {
		RBStatus child_status = insert(node->right, data);
		return modify_right(node, child_status);
	}
}

template<class T>
inline RBStatus RBTree<T>::modify_left(TreeNode<T>* &node, RBStatus child_status) {
	Node<T>* aunt = (Node<T>*)node->right;
	Color aunt_color = aunt ? aunt->color : BLACK;
	switch (child_status) {
	case NODE_RED:
		return (((Node<T>*)node)->color == RED) ? LEFT_RED : SUCCESS;
	case LEFT_RED:
		return (aunt_color == BLACK) ? rotate_right(node) :flip_color(node);
	case RIGHT_RED:
		return (aunt_color == BLACK) ? double_rotate_right(node) : flip_color(node);
	default:
		// child_status == SUCCESS
		return SUCCESS;
	}
}

template<class T>
inline RBStatus RBTree<T>::modify_right(TreeNode<T>* &node, RBStatus child_status) {
	Node<T>* aunt = (Node<T>*)node->left;
	Color aunt_color = aunt ? aunt->color : BLACK;
	switch (child_status) {
	case NODE_RED:
		return (((Node<T>*)node)->color == RED) ? RIGHT_RED : SUCCESS;
	case RIGHT_RED:
		return (aunt_color == BLACK) ? rotate_left(node) : flip_color(node);
	case LEFT_RED:
		return (aunt_color == BLACK) ? double_rotate_left(node) : flip_color(node);
	default:
		// child_status == SUCCESS
		return SUCCESS;
	}
}


template<class T>
inline RBStatus RBTree<T>::flip_color(TreeNode<T>* _node) {
	flip_color_single(_node->right);
	flip_color_single(_node->left);
	return flip_color_single(_node);
}


template<class T>
inline RBStatus RBTree<T>::flip_color_single(TreeNode<T>* _node) {
	if (_node == NULL) {
		return SUCCESS;
	}
	Node<T>* node = (Node<T>*)_node;
	if (node->color == RED) {
		node->color = BLACK;
		return SUCCESS;
	} else {
		node->color = RED;
		return NODE_RED;
	}
}

template<class T>
inline RBStatus RBTree<T>::rotate_right(TreeNode<T>* &k2) {
	TreeNode<T>* k1 = k2->left;
	k2->left = k1->right;
	k1->right = k2;
	k2 = k1;
	flip_color_single(k2->right);
	return flip_color_single(k2);
}

template<class T>
inline RBStatus RBTree<T>::double_rotate_right(TreeNode<T>* &k3) {
	rotate_left(k3->left);
	rotate_right(k3);
	flip_color_single(k3->left);
	return flip_color_single(k3);
}

template<class T>
inline RBStatus RBTree<T>::rotate_left(TreeNode<T>* &k2) {
	TreeNode<T>* k1 = k2->right;
	k2->right = k1->left;
	k1->left = k2;
	k2 = k1;
	flip_color_single(k2->left);
	return flip_color_single(k2);
}

template<class T>
inline RBStatus RBTree<T>::double_rotate_left(TreeNode<T>* &k3) {
	rotate_right(k3->right);
	rotate_left(k3);
	flip_color_single(k3->right);
	return flip_color_single(k3);
}
