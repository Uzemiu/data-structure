#pragma once
#include "LinkedList.h"
#include "String.h"
#include "Algorithm.h"
#include <string>

using namespace std;

template<class T>
class SortableList : public LinkedList<T> {

public:
	void radix_sort();

	void insertion_sort();

	void selection_sort();

	void shell_sort();

	void quick_sort();

	void merge_sort();
protected:
	using LinkedList<T>::_size;

private:
	int alphabetic_order(char c);

	template<class Fun>
	void _sort(Fun sort_fun);

};

template<class T>
void SortableList<T>::radix_sort() {
	int size = LinkedList<T>::_size;
	if (size == 0) return;
	if (!(is_base_of<string, T>::value
		|| is_base_of<String, T>::value)) {
		throw "Radix sort not supported";
	}
	LinkedList<string> bucket[28];
	int str_len = LinkedList<T>::head->ele.length();
	for (int i = str_len - 1; i >= 0; i--) {
		while (!LinkedList<T>::empty()) {
			T str = LinkedList<T>::pop_first();
			int order = alphabetic_order(str[i]);
			bucket[order].push_last(str);
		}
		// rethread
		for (int j = 0; j < 28; j++) {
			while (!bucket[j].empty()) {
				T str = bucket[j].pop_first();
				LinkedList<T>::push_last(str);
			}
		}
	}
}

template<class T>
inline void SortableList<T>::insertion_sort() {
	this->_sort(Algorithm::insertion_sort<T>);
}

template<class T>
inline void SortableList<T>::selection_sort() {
	this->_sort(Algorithm::selection_sort<T>);
}

template<class T>
inline void SortableList<T>::shell_sort() {
	this->_sort(Algorithm::shell_sort<T>);
}

template<class T>
inline void SortableList<T>::quick_sort() {
	this->_sort(Algorithm::quick_sort<T>);
}

template<class T>
inline void SortableList<T>::merge_sort() {
	this->_sort(Algorithm::merge_sort<T>);
}

template<class T>
int SortableList<T>::alphabetic_order(char c) {
	if (c == ' ') return 0;
	if (islower(c)) return c - 'a' + 1;
	if (isupper(c)) return c - 'A' + 1;
	return 27;
}

template<class T>
template<class Fun>
inline void SortableList<T>::_sort(Fun _sort_fun) {
	T* arr = LinkedList<T>::to_array();
	_sort_fun(arr, _size);
	for (int i = 0; i < _size; i++) {
		LinkedList<T>::get(i) = arr[i];
	}
	delete[] arr;
}
