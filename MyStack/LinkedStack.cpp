#include "LinkedList.h"
#include "LinkedStack.h"

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
	return LinkedStack<T>::empty();
}

template<class T>
void LinkedStack<T>::clear() {
	LinkedStack<T>::clear();
}
