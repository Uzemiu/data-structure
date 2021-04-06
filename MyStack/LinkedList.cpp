#include "LinkedList.h"
#include <iostream>

template<class T>
LinkedList<T>::LinkedList() {
	_size = 0;
	head = nullptr;
}

template<class T>
LinkedList<T>::LinkedList(const LinkedList<T> &list) {
	_size = 0;
	head = nullptr;
	Node<T>* node = list.head;
	if(node){
		do {
			push_last(node->ele);
			node = node->next;
		} while (node != list.head);
	}
}

template<class T>
LinkedList<T>::~LinkedList() {
	clear();
}

template<class T>
const LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& list) {
	_size = 0;
	head = nullptr;
	Node<T>* node = list.head;
	if (node) {
		do {
			push_last(node->ele);
			node = node->next;
		} while (node != list.head);
	}
	return *this;
}

template<class T>
void LinkedList<T>::push(const T &ele) {
	push_last(ele);
}

template<class T>
T LinkedList<T>::pop() {
	return pop_first();
}

template<class T>
T& LinkedList<T>::peek() {
	if (empty()) throw "Empty queue";
	return head->ele;
}

template<class T>
void LinkedList<T>::push_first(const T &ele) {
	insert(0, ele, false);
}

template<class T>
void LinkedList<T>::push_last(const T &ele) {
	insert(0, ele, true);
}

template<class T>
T& LinkedList<T>::peek_first() {
	if (empty()) {
		throw "Empty list";
	}
	return head->ele;
}

template<class T>
T& LinkedList<T>::peek_last() {
	if (empty()) {
		throw "Empty list";
	}
	return head->prev->ele;
}

template<class T>
T LinkedList<T>::pop_first() {
	if (empty()) {
		throw "Empty list";
	}
	return remove(0);
}

template<class T>
T LinkedList<T>::pop_last() {
	if (empty()) {
		throw "Empty list";
	}
	T t = remove(head->prev);
	return t;
}

template<class T>
int LinkedList<T>::find(const T &ele) {
	if (empty()) return -1;
	Node<T>* node = head;
	int i = 0;
	do {
		if (node->ele == ele) return i;
		node = node->next;
		i++;
	} while (node != head);
	return -1;
}

template<class T>
T& LinkedList<T>::get(int index) {
	if (empty() || index < 0) throw "Index out of bound";
	Node<T>* node = head;
	for (int i = 0; i < index; i++) {
		node = node->next;
	}
	return node->ele;
}

template<class T>
void LinkedList<T>::insert(int i, const T &ele) {
	insert(i, ele, false);
}

template<class T>
T LinkedList<T>::remove(int i) {
	if (empty()) {
		throw "Empty list";
	}
	Node<T>* node = head;
	for (int j = 0; j < i; j++) {
		node = node->next;
	}
	return remove(node);
}

template<class T>
template<class Fun>
void LinkedList<T>::for_each(Fun fun) {
	if (empty()) return;
	Node<T>* node = head;
	do {
		fun(node->ele);
		node = node->next;
	} while (node != head);
}

template<class T>
T* LinkedList<T>::to_array() {
	T* arr = new T[_size];
	int i = 0;
	for_each([&i, arr](T& ele) {
		arr[i++] = ele;
			 });
	return arr;
}

template<class T>
size_t LinkedList<T>::size() {
	return _size;
}

template<class T>
bool LinkedList<T>::empty() const {
	return _size == 0;
}

template<class T>
void LinkedList<T>::clear() {
	Node<T>* node = head;
	for (;_size;--_size) {
		Node<T>* tmp = node;
		node = node->next;
		delete tmp;
	}
	head = nullptr;
}

template<class T>
void LinkedList<T>::insert(int i, T ele, bool last) {
	Node<T>* next = head;
	Node<T>* newN = new Node<T>(ele);
	if (next) {
		if (i > _size) {
			i = _size;
		}
		for (int j = 0; j < i; j++) {
			next = next->next;
		}
		Node<T>* prev = next->prev;
		newN->prev = prev;
		newN->next = next;
		prev->next = newN;
		next->prev = newN;

		if (!last && i == 0) {
			head = newN;
		}

	} else {
		head = newN;
		head->next = head;
		head->prev = head;
	}
	_size++;
}

template<class T>
T LinkedList<T>::remove(Node<T>* node) {
	Node<T>* prev = node->prev;
	node->prev->next = node->next;
	node->next->prev = node->prev;
	T ele = T(node->ele);
	if (node == head) {
		head = head->next;
	}
	delete node;
	_size--;
	if (_size == 0) {
		head = nullptr;
	}
	return ele;
}
