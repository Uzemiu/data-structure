#pragma once
#include "BinarySearchTree.h"

#include <iostream>

using namespace std;

template<class T>
class RBTree: BinarySearchTree<T> {
public:

	RBTree(){
		NIL = new Node<T>();
		NIL->left = NIL->right = NIL->parent = NULL;
		NIL->color = BLACK;
		root = NIL;
		_size = 0;
	}

	bool insert(const T& data);
	bool remove(const T& data);
	void clear();

protected:

	template<class T>
	struct Node: public TreeNode<T> {

		TreeNode<T>* parent;
		Node() {}
		Node(T ele):Node(ele, RED) {}
		Node(T ele, Color color) :TreeNode<T>::TreeNode(ele, NULL, NULL) {
			this->color = color;
			this->parent = NULL;
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

	Node<T>* NIL;

	void remove(TreeNode<T>* node);

	void insert_fixup(TreeNode<T>* z);
	void remove_fixup(TreeNode<T>* z);

	void right_rotate(TreeNode<T>* x);
	void left_rotate(TreeNode<T>* x);

	TreeNode<T>* find(const T& data);
	TreeNode<T>* successor(TreeNode<T>* node);
};

template<class T>
inline bool RBTree<T>::insert(const T& data) {
	Node<T>* newNode = new Node<T>(data, RED);
	newNode->left = newNode->right = newNode->parent = NIL;

	TreeNode<T>* node = root;
	TreeNode<T>* parent = NIL;

	while (node != NIL) {
		parent = node;
		if (data < node->ele) {
			node = node->left;
		} else if (data > node->ele) {
			node = node->right;
		} else {
			return false;
		}
	}

	newNode->set_parent(parent);

	if (parent == NIL) {
		// root is NULL
		root = newNode;
	} else {
		if (newNode->ele < parent->ele) {
			parent->left = newNode;
		} else {
			parent->right = newNode;
		}
	}

	insert_fixup(newNode);

	return true;
}

template<class T>
inline bool RBTree<T>::remove(const T& data) {
	TreeNode<T>* node = find(data);
	if (node == NIL) {
		return false;
	}
	remove(node);
	return true;
}

template<class T>
inline void RBTree<T>::clear() {
}

template<class T>
inline void RBTree<T>::remove(TreeNode<T>* z) {
	TreeNode<T>* x = NIL; // 删除节点后补位的子节点
	TreeNode<T>* y; // 待删除节点

	if (z->left == NIL || z->right == NIL) {
		y = z;
	} else {
		// z有左右子树情况，与后继节点交换元素并删除后继节点(1)
		y = successor(z);
	}

	// 单子树或叶节点情况
	if (y->left != NIL) {
		x = y->left;
	} else {
		x = y->right;
	}
	x->set_parent(y->get_parent());
	if (y->get_parent() == NIL) {
		root = x;
	} else {
		if (y == y->get_parent()->left) {
			y->get_parent()->left = x;
		} else {
			y->get_parent()->right = x;
		}
	}

	if (y != z) {
		// z有左右子树情况，与后继节点交换元素并删除后继节点(2)
		z->ele = y->ele;
	}
	if (y->get_color() == BLACK) {
		remove_fixup(x);
	}

	delete y;
}

template<class T>
inline void RBTree<T>::insert_fixup(TreeNode<T>* z) {
	for (TreeNode<T>* zp = z->get_parent();
		 zp && zp->get_color() == RED;
		 zp = z->get_parent()) {

		TreeNode<T>* zpp = zp->get_parent(); // 根节点不可能是红色

		if (zp == zpp->left) { 
			TreeNode<T>* y = zpp->right; // 叔节点 
			if (y->get_color() == RED) {
				zp->set_color(BLACK);
				y->set_color(BLACK);
				zpp->set_color(RED);
				z = zpp;
			} else {
				if (z == zp->right) {
					z = zp;
					left_rotate(z);
				}
				z->get_parent()->set_color(BLACK);
				z->get_parent()->get_parent()->set_color(RED);
				z->get_parent()->right->set_color(BLACK);
				right_rotate(z->get_parent()->get_parent());
			}
		} else {
			TreeNode<T>* y = zpp->left; // 叔节点
			if (y->get_color() == RED) {
				zp->set_color(BLACK);
				y->set_color(BLACK);
				zpp->set_color(RED);
				z = zpp;
			} else {
				if (z == zp->left) {
					z = zp;
					right_rotate(z);
				}
				z->get_parent()->set_color(BLACK);
				z->get_parent()->get_parent()->set_color(RED);
				z->get_parent()->left->set_color(BLACK);
				left_rotate(z->get_parent()->get_parent());
			}
		}
	}
	root->set_color(BLACK);
}

template<class T>
inline void RBTree<T>::remove_fixup(TreeNode<T>* x) {
	while (x != root && x->get_color() == BLACK) {
		TreeNode<T>* w; // 叔节点
		TreeNode<T>* xp = x->get_parent();
		if (xp->left == x) {
			w = xp->right;
			if (w->get_color() == RED) {
				// 红色叔节点，转化为黑色叔节点情况
				w->set_color(BLACK);
				xp->set_color(RED);
				left_rotate(xp);
				w = xp->right;
			}
			if (w->left->get_color() == BLACK && w->right->get_color() == BLACK) {
				// 双黑子树情况，进行上溯
				w->set_color(RED);
				x = xp;
			} else {
				if (w->right->get_color() == BLACK) {
					// 子树左红右黑
					w->left->set_color(BLACK);
					w->set_color(RED); // 交换w与其左子节点颜色
					right_rotate(w); // 对w右旋
					w = xp->right; // 转化为左黑右红情况 
				}
				w->set_color(xp->get_color());
				xp->set_color(BLACK);
				w->right->set_color(BLACK);
				left_rotate(xp);
				x = root;
			}
		} else {
			w = xp->left;
			if (w->get_color() == RED) {
				// 红色叔节点，转化为黑色叔节点情况
				w->set_color(BLACK);
				xp->set_color(RED);
				left_rotate(xp);
				w = xp->left;
			}
			if (w->right->get_color() == BLACK && w->left->get_color() == BLACK) {
				// 双黑子树情况，进行上溯
				w->set_color(RED);
				x = xp;
			} else {
				if (w->left->get_color() == BLACK) {
					// 子树左红右黑
					w->right->set_color(BLACK);
					w->set_color(RED); // 交换w与其左子节点颜色
					right_rotate(w); // 对w右旋
					w = xp->left; // 转化为左黑右红情况 
				}
				w->set_color(xp->get_color());
				xp->set_color(BLACK);
				w->left->set_color(BLACK);
				left_rotate(xp);
				x = root;
			}
		}
	}
	x->set_color(BLACK);
}

template<class T>
inline void RBTree<T>::right_rotate(TreeNode<T>* x) {
	TreeNode<T>* xp = x->get_parent();
	TreeNode<T>* y = x->left;
	if (xp == NIL) {
		root = y;
	} else {
		if (x == xp->right) {
			xp->right = y;
		} else {
			xp->left = y;
		}
	}
	y->set_parent(xp);
	x->left = y->right;
	y->right->set_parent(x);
	y->right = x;
	x->set_parent(y);
}

template<class T>
inline void RBTree<T>::left_rotate(TreeNode<T>* x) {
	TreeNode<T>* xp = x->get_parent();
	TreeNode<T>* y = x->right;
	if (xp == NIL) {
		root = y;
	} else {
		if (x == xp->left) {
			xp->left = y;
		} else {
			xp->right = y;
		}
	}
	y->set_parent(xp);
	x->right = y->left;
	y->left->set_parent(x);
	y->left = x;
	x->set_parent(y);
}

template<class T>
inline TreeNode<T>* RBTree<T>::find(const T& data) {
	TreeNode<T>* node = root;
	while (node != NIL) {
		if (data == node->ele) {
			return node;
		} else if (data < node->ele) {
			node = node->left;
		} else {
			node = node->right;
		}
	}
	return node;
}

template<class T>
inline TreeNode<T>* RBTree<T>::successor(TreeNode<T>* x) {
	if (x->right != NIL) {
		x = x->right;
		while (x->left != NIL) x = x->left;
		return x;
	}
	TreeNode<T>* y = x->get_parent();
	while (y != NIL && x == y->right) {
		x = y;
		y = y->get_parent();
	}
	return x;
}
