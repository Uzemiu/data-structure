#include "MyDeque.h"

template<class T>
void MyDeque<T>::check_capacity() {
	if (front > max_size || rear < 0) {
		resize(max_size * 2);
	}
}

template<class T>
void MyDeque<T>::reset_position() {
	front = max_size / 2;
	rear = front - 1;
}

template<class T>
MyDeque<T>::MyDeque() {
	max_size = 100;
	element = new T[max_size];
	reset_position();
}

template<class T>
MyDeque<T>::MyDeque(size_t size) {
	max_size = size >= 2 ? size : 2;
	element = new T[max_size];
	reset_position();
}

template<class T>
void MyDeque<T>::push(const T &ele) {
	push_first(ele);
}

template<class T>
T MyDeque<T>::pop() {
	return pop_last();
}

template<class T>
void MyDeque<T>::push_first(const T &ele) {
	if (front > max_size) {
		resize(max_size * 2);
	}
	element[front++] = ele;
}

template<class T>
void MyDeque<T>::push_last(const T &ele) {
	if (rear < 0) {
		resize(max_size * 2);
	}
	element[rear--] = ele;
}

template<class T>
T& MyDeque<T>::peek() {
	if (empty()) {
		throw "Empty queue";
	}
	return element[front - 1];
}

template<class T>
T& MyDeque<T>::peek_first() {
	if (empty()) {
		throw "Empty queue";
	}
	return element[front - 1];
}

template<class T>
T& MyDeque<T>::peek_last() {
	if (empty()) {
		throw "Empty queue";
	}
	return element[rear + 1];
}

template<class T>
T MyDeque<T>::pop_first() {
	if (empty()) {
		throw "Empty queue";
	}
	return element[--front];
}

template<class T>
T MyDeque<T>::pop_last() {
	if (empty()) {
		throw "Empty queue";
	}
	return element[++rear];
}

template<class T>
size_t MyDeque<T>::size() {
	return front - rear - 1;
}

template<class T>
bool MyDeque<T>::empty() {
	return size() == 0;
}

template<class T>
void MyDeque<T>::clear() {
	reset_position();
}
// append +队尾

// 仅实现扩容
template<class T>
void MyDeque<T>::resize(size_t size) {
	T* newEle = new T[size];

	int offset = (size - max_size) / 2;
	for (int i = 0; i < max_size; i++) {
		newEle[i + offset] = element[i];
	}
	rear += offset;
	front += offset;
	max_size = size;

	delete element;
	element = newEle;
}
