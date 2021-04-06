#pragma once
#include "List.h"

template <class T>
class LinkedList: List<T>{
public:
	LinkedList();
	LinkedList(const LinkedList<T> &list);
	~LinkedList();
	const LinkedList<T>& operator=(const LinkedList<T> &list);

	void push(const T &ele);
	T pop();
	T& peek();

	void push_first(const T &ele);
	void push_last(const T &ele);
	T& peek_first();
	T& peek_last();
	T pop_first();
	T pop_last();

	int find(const T &ele);
	T& get(int index);
	void insert(int i, const T &ele);
	T remove(int i);

	template<class Fun>
	void for_each(Fun fun);

	T* to_array();

	size_t size();
	bool empty() const;
	void clear();


protected:

	template<class T>
	struct Node {
		T ele;
		Node<T>* next;
		Node<T>* prev;
		Node() : ele(T()), next(nullptr), prev(nullptr) {}
		Node(const T& ele) : ele(ele), next(nullptr), prev(nullptr) {}
	};

	Node<T>* head;
	size_t _size;

	void insert(int i, T ele, bool last);
	T remove(Node<T>* node);
};

