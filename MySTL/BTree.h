#pragma once
template<class T, int order>
class BTree {
	BTree(): root(NULL) {}

	bool search( T& data);

private:
	template<class T, int order>
	struct Node {
		int count;
		T data[order - 1];
		Node<T, order>* branch[order];
		Node() {
			count = 0;
			memset(branch, NULL, sizeof(branch));
		}
	};

	Node<T, order>* root;

	bool search(Node<T, order>* node, T& data);
	bool search(Node<T, order>* node, T& data, int &pos);
};
