#include "BTree.h"

template<class T, int order>
bool BTree<T, order>::search(T& data) {
	return search(root, data);
}

template<class T, int order>
bool BTree<T, order>::search(Node<T, order>* node, T& data) {
	bool res = false;
	int pos = 0;
	if (node) {
		res = search(node, data, pos);
		if (res) {
			data = node->data[pos];
		} else {
			res = search(node->branch[pos], data);
		}
	}
	return res;
}

template<class T, int order>
bool BTree<T, order>::search(Node<T, order>* node, T& data, int& pos) {
	pos = 0;
	while (pos < node->count && data > node->data[pos]) pos++;
	return (pos < node->count) && (data == node->data[pos]);
}
