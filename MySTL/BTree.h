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
	 * @param pos: node�ڵ�Ԫ����>=data���׸�λ��
	 * @return node�ڵ����Ƿ����data
	 */
	bool search(Node<T, order>* node, const T& data, int& pos);
	int push_down(Node<T, order>* current, const T& ele, T& median, Node<T, order>*& right_branch);
    /**
	 * @brief ��data����current�ڵ��data[pos]��
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
	* �ݹ�ɾ��
	*/
	bool remove(Node<T, order>* node, const T& data);
	/**
	* �Ƴ�Ҷ�ӽڵ�node�е�data[pos]
	*/
	void remove_data(Node<T, order>* node, int pos);
	/**
	* ɾ����Ҷ�ӽڵ�node��pos�Ĺؼ���ʱ�����ӽڵ����һ������ؼ���
	*/
	void copy_in_predecessor(Node<T, order>* node, int pos);
	/**
	* ɾ����Ҷ�ӽڵ�node��branch[pos]��Ĺؼ��ֺ�
	* branch[pos]ӵ�йؼ��������٣����ֵܽڵ��ؼ���
	*/
	void restore(Node<T, order>* node, int pos);
	/**
	* ��node->branch[pos]�Ĺؼ����Ƶ�node->branch[pos-1]
	*/
	void move_left(Node<T, order>* node, int pos);
	/**
	* ��node->branch[pos]�Ĺؼ����Ƶ�node->branch[pos+1]
	*/
	void move_right(Node<T, order>* node, int pos);
	/**
	* �ϲ�node->branch[pos],node->branch[pos-1],node->data[pos-1]������
	*/
	void combine(Node<T, order>* node, int pos);


};
