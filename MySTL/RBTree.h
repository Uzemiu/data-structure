#pragma once
#include "BinarySearchTree.h"

#include <iostream>

using namespace std;

enum RBStatus {
	DUPLICATED, SUCCESS, 
	NODE_RED, RIGHT_RED, LEFT_RED, 
	NOT_FOUND, DEL_NODE, DEL_BLACK, DEL_RED, DUAL_BLACK};

template<class T>
class RBTree: BinarySearchTree<T> {
public:
	bool insert(const T& data);
	bool remove(const T& data);

protected:

	template<class T>
	struct Node: public TreeNode<T> {

		TreeNode<T>* parent;

		Node(T ele):Node(ele, RED) {}
		Node(T ele, Color color) : 
			TreeNode<T>::TreeNode(ele, NULL, NULL) {
			this->color = color;
		}
		Color get_color() {
			return this->color;
		}
		void set_color(Color color) {
			this->color = color;
		}
		TreeNode<T>* get_parent() {
			return this->parent;
		}
		void set_parent(TreeNode<T>* parent) {
			this->parent = parent;
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

	RBStatus rotate_right(TreeNode<T>* &k2, bool flip_color = true);
	RBStatus double_rotate_right(TreeNode<T>* &k3);
	RBStatus rotate_left(TreeNode<T>* &k2, bool flip_color = true);
	RBStatus double_rotate_left(TreeNode<T>* &k3);

	RBStatus remove(TreeNode<T>*& node, const T& data);

	RBStatus del_fix_left(TreeNode<T>* &node, RBStatus child_status);
	RBStatus del_fix_right(TreeNode<T>* &node, RBStatus child_status);

	Color get_node_color(TreeNode<T>* node);
	void set_node_color(TreeNode<T>* node, Color color);
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
	Color aunt_color = get_node_color(aunt);
	switch (child_status) {
	case NODE_RED:
		return (get_node_color(node) == RED) ? LEFT_RED : SUCCESS;
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
	Color aunt_color = get_node_color(aunt);
	switch (child_status) {
	case NODE_RED:
		return (get_node_color(node) == RED) ? RIGHT_RED : SUCCESS;
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
inline RBStatus RBTree<T>::flip_color_single(TreeNode<T>* node) {
	if (node == NULL) {
		return SUCCESS;
	}
	if (node->get_color() == RED) {
		node->set_color(BLACK);
		return SUCCESS;
	} else {
		node->set_color(RED);
		return NODE_RED;
	}
}

template<class T>
inline RBStatus RBTree<T>::rotate_right(TreeNode<T>* &k2, bool flip_color) {
	TreeNode<T>* k1 = k2->left;
	k2->left = k1->right;
	k1->right = k2;
	k2 = k1;
	if (flip_color) {
		flip_color_single(k2->right);
		return flip_color_single(k2);
	} else {
		return SUCCESS;
	}
}

template<class T>
inline RBStatus RBTree<T>::double_rotate_right(TreeNode<T>* &k3) {
	rotate_left(k3->left);
	rotate_right(k3);
	flip_color_single(k3->left);
	return flip_color_single(k3);
}

template<class T>
inline RBStatus RBTree<T>::rotate_left(TreeNode<T>* &k2, bool flip_color) {
	TreeNode<T>* k1 = k2->right;
	k2->right = k1->left;
	k1->left = k2;
	k2 = k1;
	if (flip_color) {
		flip_color_single(k2->left);
		return flip_color_single(k2);
	} else {
		return SUCCESS;
	}
}

template<class T>
inline RBStatus RBTree<T>::double_rotate_left(TreeNode<T>* &k3) {
	rotate_right(k3->right);
	rotate_left(k3);
	flip_color_single(k3->right);
	return flip_color_single(k3);
}

template<class T>
inline RBStatus RBTree<T>::remove(TreeNode<T>*& node, const T& data) {
	if (node == NULL) {
		return NOT_FOUND;
	} else if (data < node->ele) {
		RBStatus status = remove(node->left, data);
		return del_fix_left(node, status);
	} else if (data > node->ele){
		RBStatus status = remove(node->right, data);
		return del_fix_right(node, status);
	} else if (node->left && node->right) {
		// 两个子节点
		TreeNode<T>* tmp = node->right;
		while (tmp->left) tmp = tmp->left; // findMin
		node->ele = tmp->ele;

		RBStatus status = remove(node->right, node->ele);
		return del_fix_right(node, status);
	} else {
		// 两个以下子节点
		TreeNode<T>* origin = node;
		node = (node->left ? node->left : node->right);
		RBStatus res = origin->color == RED ? DEL_RED : DEL_BLACK;
		delete origin;
		return res;
	}
}


template<class T>
inline RBStatus RBTree<T>::del_fix_left(TreeNode<T>*& node, RBStatus child_status) {
	TreeNode<T>* brother = node->right;
	Color node_color = get_node_color(node);
	Color brother_color = get_node_color(brother);
	Color left_child_color = get_node_color(brother->left);
	Color right_child_color = get_node_color(brother->right);

	switch (child_status) {
	case DEL_BLACK:
		return DEL_NODE;
	case DEL_NODE:
		if (get_node_color(brother) == RED) {
			// swap color
			node->set_color(brother_color);
			brother->set_color(node_color);

			// 转化为兄弟节点黑色情况
			rotate_left(node, false);
			return del_fix_left(node->left, DEL_NODE);

		} else if (left_child_color == BLACK && right_child_color == BLACK) {
			// 双子节点黑色
			brother->color = RED;
			return DEL_NODE;
		} else if (left_child_color == RED) {
			// swap color
			brother->left->color = brother_color; // TODO
			brother->set_color(left_child_color);

			// 转化为右节点红色情况
			rotate_right(node->right, false);
			return del_fix_left(node->right, DEL_NODE);

		} else {
			// 右节点红色
			brother->set_color(node_color);
			node->set_color(BLACK);
			brother->right->set_color(BLACK); // TODO

			rotate_left(node, false);
			return SUCCESS;
		}
	default:
		return SUCCESS;
	}
}

template<class T>
inline RBStatus RBTree<T>::del_fix_right(TreeNode<T>*& _node, RBStatus child_status) {
	return RBStatus();
}

template<class T>
inline Color RBTree<T>::get_node_color(TreeNode<T>* node) {
	return node ? node->get_color() : BLACK;
}

template<class T>
inline void RBTree<T>::set_node_color(TreeNode<T>* node, Color color) {
	node && node->set_color(color);
}
