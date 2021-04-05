#pragma once
#include "MyQueue.h"


template <class T>
class MyDeque : public MyQueue<T>{
public:
	MyDeque();
	MyDeque(size_t size);

	void push(const T &ele);
	T pop();
	T& peek();

	void push_first(const T &ele);
	void push_last(const T &ele);
	T& peek_first();
	T& peek_last();
	T pop_first();
	T pop_last();
	size_t size();
	bool empty();
	void clear();
		
private:
	T *element;
	int front;
	int rear;
	size_t max_size;

	void resize(size_t size);
	void check_capacity();
	void reset_position();
};

