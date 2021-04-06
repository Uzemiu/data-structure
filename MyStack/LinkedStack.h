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

