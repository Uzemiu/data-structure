#pragma once
template<class T>
class List {
	virtual int find(const T& ele) = 0;
	virtual T& get(int index) = 0;
	virtual void insert(int i, const T& ele) = 0;
	virtual T remove(int i) = 0;

	virtual size_t size() = 0;
	virtual bool empty() const = 0;
	virtual void clear() = 0;
};

template<class T>
bool operator==(const T& t1, const T& t2) {
	return &t1 == &t2;
}