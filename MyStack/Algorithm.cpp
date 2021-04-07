#include "Algorithm.h"
#include "LinkedList.cpp"

#include <algorithm>
#include <vector>

using namespace std;

template<class T>
void Algorithm::insert_sort(T* arr, int from, int to) {
	int j = 0;
	for (int i = from + 1; i <= to; i++) {
		T tmp = arr[i];
		for (j = i; j > 0 && tmp < arr[j - 1]; j--) {
			arr[j] = arr[j - 1];
		}
		arr[j] = tmp;
	}
}

template<class T>
void Algorithm::quick_sort(T* arr, int from, int to) {
	if (from + 10 <= to) {
		T pivot = median3(arr, from ,to);
		int i = from;
		int j = to - 1;
		for (;;) {
			while (arr[++i] < pivot);
			while (arr[--j] > pivot);
			if (i < j) swap(arr[i], arr[j]);
			else break;
		}
		swap(arr[i], arr[to - 1]);
		quick_sort(arr, from, i -1);
		quick_sort(arr, i+1, to);
	} else {
		insert_sort(arr, from, to);
	}
}

template<class T>
void Algorithm::heap_sort(T* arr, int len) {
	// build heap
	for (int i = len / 2 - 1; i >= 0; i--) {
		insert_heap(arr, i, len);
	}

	for (int i = len; i > 0; i--) {
		swap(arr[0], arr[i]);
		insert_heap(arr, 0, i - 1);
	}

}

template<class T>
T Algorithm::median3(T* arr, int from, int to) {
	int center = (from + to) / 2;
	if (arr[center] < arr[from])
		swap(arr[center], arr[to]);
	if (arr[to] < arr[from])
		swap(arr[to], arr[from]);
	if (arr[to] < arr[center])
		swap(arr[to], arr[center]);
	// place pivot at right -1;
	swap(arr[center], arr[to - 1]);
	return arr[to - 1];
}

template<class T>
void Algorithm::insert_heap(T *arr, int i, int to) {
	T tmp = arr[i];
	for (int j = i * 2 + 1; j <= to; j = j * 2 + 1) {
		if (j < to && arr[j] < arr[j + 1]) {
			j++;
		}
		if (arr[j] > tmp) {
			arr[i] = arr[j];
			i = j;
		} else {
			break;
		}
	}
	arr[i] = tmp;
}

void Algorithm::radix_sort(string* arr, int len) {
	if (!arr) return;
	LinkedList<string> bucket[MAX_CHAR];
	int str_len = arr[0].length();
	for (int i = str_len; i >= 0; i--) {
		for (int j = 0; j < len; j++) {
			int order = alphabetic_order(arr[j][i]);
			bucket[order].push_last(arr[j]);
		}
		// rethread
		int j = 0;

	}
}

int Algorithm::alphabetic_order(char c) {
	if (c == ' ') return 0;
	if (islower(c)) return c - 'a' + 1;
	if (isupper(c)) return c - 'A' + 1;
	return 27;
}

void Algorithm::rethread(LinkedList<string> bucket[28]) {
}
