#pragma once
#include <iostream>
template<class T, int order>
class BTree {
public:
	BTree(): root(NULL) {}
	~BTree();

	bool search(T& data);
	bool insert(const T& data);
	bool remove(const T& data);
	void clear();

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

	const static int STATUS_OVERFLOW = 2;
	const static int STATUS_DUPLICATE = 1;
	const static int STATUS_SUCCESS = 0;

	Node<T, order>* root;

	void clear(Node<T, order>* node);

	bool search(Node<T, order>* node, T& data);
	/**
	 * @param pos: node节点元素中>=data的首个位置
	 * @return node节点中是否存在data
	 */
	bool search(Node<T, order>* node, const T& data, int& pos);
	int push_down(Node<T, order>* current, const T& ele, T& median, Node<T, order>*& right_branch);
    /**
	 * @brief 将data插入current节点的data[pos]中
	 */
	void push_in(Node<T, order>* current, const T& data, Node<T, order>*& right_branch, int pos);
	/**
	 * @param current: the node to be split
	 * @param pos: where extra entry goes
	 */
	void split_node(Node<T, order>* current, // to be split
					const T& data,
					Node<T, order>*& extra_branch,
					int pos, // where extra entry goes
					Node<T, order>*& right_half,
					T& median);

	/**
	* 递归删除
	*/
	bool remove(Node<T, order>* node, const T& data);
	/**
	* 移除叶子节点node中的data[pos]
	*/
	void remove_data(Node<T, order>* node, int pos);
	/**
	* 删除非叶子节点node中pos的关键字时，向子节点借上一个升序关键字
	*/
	void copy_in_predecessor(Node<T, order>* node, int pos);
	/**
	* 删除非叶子节点node中branch[pos]里的关键字后，
	* branch[pos]拥有关键字数过少，向兄弟节点借关键字
	*/
	void restore(Node<T, order>* node, int pos);
	/**
	* 将node->branch[pos]的关键字移到node->branch[pos-1]
	*/
	void move_left(Node<T, order>* node, int pos);
	/**
	* 将node->branch[pos]的关键字移到node->branch[pos+1]
	*/
	void move_right(Node<T, order>* node, int pos);
	/**
	* 合并node->branch[pos],node->branch[pos-1],node->data[pos-1]中数据
	*/
	void combine(Node<T, order>* node, int pos);


};

template<class T, int order>
BTree<T, order>::~BTree() {
	clear();
}

template<class T, int order>
bool BTree<T, order>::search(T& data) {
	return search(root, data);
}

template<class T, int order>
bool BTree<T, order>::insert(const T& data) {
	T median;
	Node<T, order>* right_branch, * new_root;
	int res = push_down(root, data, median, right_branch);
	if (res == STATUS_OVERFLOW) {
		new_root = new Node<T, order>;
		new_root->count = 1;
		new_root->data[0] = median;
		new_root->branch[0] = root;
		new_root->branch[1] = right_branch;
		root = new_root;
		return true;
	}
	return res;
}

template<class T, int order>
bool BTree<T, order>::remove(const T& data) {
	bool res = remove(root, data);
	if (root && root->count == 0) {
		Node<T, order>* old = root;
		root = root->branch[0];
		delete old;
	}
	return res;
}

template<class T, int order>
void BTree<T, order>::clear() {
	clear(root);
	root = NULL;
}

template<class T, int order>
void BTree<T, order>::clear(Node<T, order>* node) {
	if (node) {
		for (int i = 0; i <= node->count; i++) {
			clear(node->branch[i]);
		}
	}
	delete node;
}

template<class T, int order>
bool BTree<T, order>::search(Node<T, order>* node, T& data) {
	if (!node) {
		return false;
	}
	bool res = false;
	int pos = search(node, data, pos);
	if (res) {
		data = node->data[pos];
	} else {
		res = search(node->branch[pos], data);
	}
	return res;
}

template<class T, int order>
bool BTree<T, order>::search(Node<T, order>* node, const T& data, int& pos) {
	pos = 0;
	for (; pos < node->count && data > node->data[pos]; pos++);
	return (pos < node->count) && (data == node->data[pos]);
}

template<class T, int order>
int BTree<T, order>::push_down(Node<T, order>* current, const T& ele, T& median, Node<T, order>*& right_branch) {
	if (!current) {
		median = ele;
		right_branch = NULL;
		return STATUS_OVERFLOW;
	}
	int pos = 0;
	if (search(current, ele, pos)) {
		return STATUS_DUPLICATE;
	}
	T extra_ele;
	Node<T, order>* extra_branch;
	int res = push_down(current->branch[pos], ele, extra_ele, extra_branch);
	if (res == STATUS_OVERFLOW) {
		// entry now must be add to current
		if (current->count < order - 1) {
			// enough space
			push_in(current, extra_ele, extra_branch, pos);
			return STATUS_SUCCESS;
		}
		// median and its right branch will go up to a higher node
		split_node(current, extra_ele, extra_branch, pos, right_branch, median);
	}
	return res;
}

template<class T, int order>
void BTree<T, order>::push_in(Node<T, order>* current, const T& ele, Node<T, order>*& right_branch, int pos) {
	for (int i = current->count; i > pos; i--) {
		current->data[i] = current->data[i - 1];
		current->branch[i + 1] = current->branch[i];
	}
	current->data[pos] = ele;
	current->branch[pos + 1] = right_branch;
	current->count++;
}

template<class T, int order>
void BTree<T, order>::split_node(Node<T, order>* current, const T& ele,
								 Node<T, order>*& extra_branch, int pos,
								 Node<T, order>*& right_half, T& median) {
	right_half = new Node<T, order>;
	int mid = order / 2; // entries from mid on will go ro right half
	if (pos > mid) {
		// new entry belongs in right half
		// temporarily leave the median in left half
		mid++;
		for (int i = mid; i < order - 1; i++) {
			right_half->data[i - mid] = current->data[i];
			right_half->branch[i - mid + 1] = current->branch[i + 1];
		}
		current->count = mid;
		right_half->count = order - mid - 1;
		push_in(right_half, ele, extra_branch, pos - mid);
	} else {
		// move entries to right half
		for (int i = mid; i < order - 1; i++) {
			right_half->data[i - mid] = current->data[i];
			right_half->branch[i - mid + 1] = current->branch[i + 1];
		}
		current->count = mid;
		right_half->count = order - mid - 1;
		push_in(current, ele, extra_branch, pos);
	}
	median = current->data[current->count - 1];
	// remove median from left half
	right_half->branch[0] = current->branch[current->count]; // 
	current->count--;
}

template<class T, int order>
bool BTree<T, order>::remove(Node<T, order>* node, const T& data) {
	if (!node) {
		return false;
	}
	bool res = false;
	int pos = 0;
	if (search(node, data, pos)) {
		// target in node
		if (node->branch[pos]) {
			// not leaf
			copy_in_predecessor(node, pos);
			remove(node->branch[pos], node->data[pos]);
		} else {
			remove_data(node, pos);
		}
		res = true;
	} else {
		res = remove(node->branch[pos], data);
	}
	if (node->branch[pos] && node->branch[pos]->count < (order - 1) / 2) {
		restore(node, pos);
	}
	return res;
}

template<class T, int order>
void BTree<T, order>::remove_data(Node<T, order>* node, int pos) {
	for (int i = pos; i < node->count - 1; i++) {
		node->data[i] = node->data[i + 1];
	}
	node->count--;
}

template<class T, int order>
void BTree<T, order>::copy_in_predecessor(Node<T, order>* node, int pos) {
	Node<T, order>* leaf = node->branch[pos];
	for (; leaf->branch[leaf->count]; leaf = leaf->branch[leaf->count]);
	node->data[pos] = leaf->data[leaf->count - 1];
}

template<class T, int order>
void BTree<T, order>::restore(Node<T, order>* node, int pos) {
	// rightmost branch
	if (pos == node->count) {
		if (node->branch[pos - 1]->count > (order - 1) / 2) {
			move_right(node, pos - 1);
		} else {
			combine(node, pos);
		}
	} else if (pos == 0) { // rightmost branch
		if (node->branch[1]->count > (order - 1) / 2) {
			move_left(node, 1);
		} else {
			combine(node, 1);
		}
	} else { // intermediate branches
		if (node->branch[pos - 1]->count > (order - 1) / 2) {
			move_right(node, pos - 1);
		} else if (node->branch[pos + 1]->count > (order - 1) / 2) {
			move_left(node, pos + 1);
		} else {
			combine(node, pos);
		}
	}
}

template<class T, int order>
void BTree<T, order>::move_left(Node<T, order>* node, int pos) {
	Node<T, order>* left_branch = node->branch[pos - 1],
		* right_branch = node->branch[pos];
	// 先向父节点借
	left_branch->data[left_branch->count] = node->data[pos - 1];
	left_branch->branch[++left_branch->count] = right_branch->branch[0];
	// 父节点再向右兄弟节点借
	node->data[pos - 1] = right_branch->data[0];
	right_branch->count--;
	// 复制被借关键字的右兄弟的元素
	for (int i = 0; i < right_branch->count; i++) {
		right_branch->data[i] = right_branch->data[i + 1];
		right_branch->branch[i] = right_branch->branch[i + 1];
	}
	right_branch->branch[right_branch->count] =
		right_branch->branch[right_branch->count + 1];
}

template<class T, int order>
void BTree<T, order>::move_right(Node<T, order>* node, int pos) {
	Node<T, order>* left_branch = node->branch[pos],
		* right_branch = node->branch[pos + 1];
	// 复制元素并给新元素腾出空间
	right_branch->branch[right_branch->count + 1] =
		right_branch->branch[right_branch->count];
	for (int i = right_branch->count; i > 0; i--) {
		right_branch->data[i] = right_branch->data[i - 1];
		right_branch->branch[i] = right_branch->branch[i - 1];
	}
	right_branch->count++;
	// 先向父节点借
	right_branch->data[0] = node->data[pos];
	right_branch->branch[0] = left_branch->branch[left_branch->count--];
	// 父节点再向左兄弟节点借
	node->data[pos] = left_branch->data[left_branch->count];
}

template<class T, int order>
void BTree<T, order>::combine(Node<T, order>* node, int pos) {
	Node<T, order>* left_branch = node->branch[pos - 1],
		* right_branch = node->branch[pos];
	// 左子树先复制父节点data[pos-1]元素
	left_branch->data[left_branch->count] = node->data[pos - 1];
	left_branch->branch[++left_branch->count] = right_branch->branch[0];
	// 复制右子树数据进左子树
	for (int i = 0; i < right_branch->count; i++) {
		left_branch->data[left_branch->count] = right_branch->data[i];
		left_branch->branch[++left_branch->count] =
			right_branch->branch[i + 1];
	}
	// 父节点中一个关键字被合并之后移动父节点数据
	node->count--;
	for (int i = pos - 1; i < node->count; i++) {
		node->data[i] = node->data[i + 1];
		node->branch[i + 1] = node->branch[i + 2];
	}
	delete right_branch;
}
