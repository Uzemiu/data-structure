#pragma once
#include <iostream>
template<class T, int order>
class BTree {
public:
	BTree(): root(NULL) {}

	bool search(T& data);
	bool insert(const T& data);
	bool remove(const T& data);

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
