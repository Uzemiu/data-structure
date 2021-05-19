#pragma once
#include "LinkedList.h"
#include <iostream>

using namespace std;

template<class T>
class OrderedList: public LinkedList<T>{
public:
	void insert(const T& ele);
	void replace(int i, const T& ele);

private:
	using LinkedList<T>::_size;
};

template<class T>
inline void OrderedList<T>::insert(const T& ele) {
	int i = 0;
	for (; i < _size && LinkedList<T>::get(i) < ele; i++);
	LinkedList<T>::insert(i, ele);
}

template<class T>
inline void OrderedList<T>::replace(int i, const T& ele) {
	LinkedList<T>::remove(i);
	insert(ele);
}
