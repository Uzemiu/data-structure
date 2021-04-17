#include "LinkedList.h"
#include "SortableList.h"

#include <string>

using namespace std;

template<class T>
void SortableList<T>::radix_sort() {
	int size = LinkedList<T>::_size;
	if (size == 0) return;
	if (!is_base_of<string, T>::value 
		|| is_base_of<String, T>::value) {
		throw "Radix sort not supported";
	}
	LinkedList<string> bucket[28];
	int str_len = LinkedList<T>::head->ele.length();
	for (int i = str_len - 1; i >= 0; i--) {
		while (!LinkedList<T>::empty()){
			string str = LinkedList<T>::pop_first();
			int order = alphabetic_order(str[i]);
			bucket[order].push_last(str);
		}
		// rethread
		for (int j = 0; j < 28; j++) {
			while (!bucket[j].empty()) {
				string str = bucket[j].pop_first();
				LinkedList<T>::push_last(str);
			}
		}
	}
}

template<class T>
int SortableList<T>::alphabetic_order(char c) {
	if (c == ' ') return 0;
	if (islower(c)) return c - 'a' + 1;
	if (isupper(c)) return c - 'A' + 1;
	return 27;
}
