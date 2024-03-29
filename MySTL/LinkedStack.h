#pragma once
#include "LinkedList.h"

template<class T>
class LinkedStack : private LinkedList<T>{
public:
	T pop();
	void push(const T& e);
	T& peek();
	size_t size();
	bool empty();
	void clear();
};

template<class T>
T LinkedStack<T>::pop() {
	return LinkedList<T>::pop_last();
}

template<class T>
void LinkedStack<T>::push(const T& e) {
	LinkedList<T>::push_last(e);
}

template<class T>
T& LinkedStack<T>::peek() {
	return LinkedList<T>::peek_last();
}

template<class T>
size_t LinkedStack<T>::size() {
	return LinkedList<T>::size();
}

template<class T>
bool LinkedStack<T>::empty() {
	return LinkedList<T>::empty();
}

template<class T>
void LinkedStack<T>::clear() {
	LinkedList<T>::clear();
}

