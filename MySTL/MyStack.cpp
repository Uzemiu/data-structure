#include "MyStack.h"

template<class T>
T MyStack<T>::pop() {
	if (top == 0) {
		throw "Underflow exception";
	}
	return element[--top];
}

template <class T>
void MyStack<T>::push(T e) {
	if (top >= max_size) {
		resize(max_size << 1);
	}
	element[top++] = e;
}

template<class T>
size_t MyStack<T>::size() {
	return top;
}

template<class T>
T MyStack<T>::peek() {
	if (top == 0) {
		throw "Underflow exception";
	}
	return element[top - 1];
}

template<class T>
bool MyStack<T>::empty() {
	return top == 0;
}

template<class T>
void MyStack<T>::clear() {
	top = 0;
}

template<class T>
void MyStack<T>::resize(size_t size) {
	T* newEle = new T[size];
	for (int i = 0; i < max_size; i++) {
		newEle[i] = element[i];
	}
	max_size = size;

	delete element;
	element = newEle;
}

