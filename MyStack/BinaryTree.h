#pragma once
template<class T>
class BinaryTree {
public:
	void insert(T ele);

	template<class Fun>
	void preorder_traverse(Fun fun);
	template<class Fun>
	void inorder_traverse(Fun fun);
	template<class Fun>
	void postorder_traverse(Fun fun);


protected:
	template<class T>
	struct Node {
		T ele;
		Node<T>* left;
		Node<T>* right;
	};

	Node<T>* root;
};

