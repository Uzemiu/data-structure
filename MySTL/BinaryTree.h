#pragma once
#include "LinkedStack.h"
#include <iostream>
#include <vector>
using namespace std;

template<class T>
struct TreeNode {
	T ele;
	TreeNode<T>* left;
	TreeNode<T>* right;
	TreeNode(T ele) : TreeNode::TreeNode(ele, NULL, NULL) {}
	TreeNode(T ele, TreeNode<T>* left, TreeNode<T>* right) 
		:ele(ele), left(left), right(right) {}
};

template<class T>
class BinaryTree {
public:
	BinaryTree();
	BinaryTree(const BinaryTree<T> &original);
	BinaryTree<T>& operator=(const BinaryTree<T>& original);
	~BinaryTree();

	void insert(const T &ele);
	int size() const;
	bool empty() const;
	void clear();
	int height() const;

	template<class Fun>
	void pre_order_traverse(Fun apply);

	template<class Fun>
	void in_order_traverse(Fun apply);

	template<class Fun>
	void post_order_traverse(Fun apply);

	template<class Fun>
	void level_order_traverse(Fun apply);


protected:
	TreeNode<T>* root;
	int _size;

private:
	void clear(TreeNode<T>* node);
	void copy(TreeNode<T>* src, TreeNode<T>* &dest);
};

