#pragma once
template <class T>
class MyQueue {
public:
	virtual void push(const T &ele) = 0;
	virtual T pop() = 0;
	virtual T& peek() = 0;
	virtual size_t size() = 0;
	virtual bool empty() = 0;
	virtual void clear() = 0;

};

