#pragma once
#include "LinkedList.h"
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

class Algorithm {
public:
	template<class T>
	static void insertion_sort(T* arr, int len);

	template<class T>
	static void quick_sort(T* arr, int len);

	template<class T>
	static void selection_sort(T* arr, int len);

	template<class T>
	static void shell_sort(T* arr, int len);

	template<class T>
	static void heap_sort(T* arr, int len);

	template<class T>
	static void merge_sort(T* arr, int len);

private:
	// for quick sort
	template<class T>
	static T median3(T* arr, int from, int to);
	template<class T>
	static void quick_sort(T* arr, int from, int to);

	// for heap sort
	template<class T>
	static void insert_heap(T *arr, int i, int len);

	// for merge sort
	template<class T>
	static void merge_sort(T* arr, int low, int high);
	template<class T>
	static void merge(T* arr, int low, int mid, int high);

};

template<class T>
void Algorithm::insertion_sort(T* arr, int len) {
	for (int i = 1; i < len; i++) {
		T tmp = arr[i];
		int j = i;
		for (; j > 0 && tmp < arr[j - 1]; j--) {
			arr[j] = arr[j - 1];
		}
		arr[j] = tmp;
	}
}

template<class T>
inline void Algorithm::quick_sort(T* arr, int len) {
	Algorithm::quick_sort(arr, 0, len - 1);
}

template<class T>
void Algorithm::quick_sort(T* arr, int from, int to) {
	if (from + 10 < to) {
		T pivot = median3(arr, from, to);
		int i = from;
		int j = to - 1;
		for (;;) {
			while (arr[++i] < pivot);
			while (arr[--j] > pivot);
			if (i < j) swap(arr[i], arr[j]);
			else break;
		}
		swap(arr[i], arr[to - 1]);
		quick_sort(arr, from, i - 1);
		quick_sort(arr, i + 1, to);
	} else {
		insertion_sort(arr+from, to-from+1);
	}
}

template<class T>
void Algorithm::selection_sort(T* arr, int len) {
	for (int i = 0; i < len; i++) {
		int min_ = i;
		for (int j = i + 1; j < len; j++) {
			if (arr[j] < arr[min_]) {
				min_ = j;
			}
		}
		swap(arr[min_], arr[i]);
	}
}

template<class T>
void Algorithm::shell_sort(T* arr, int len) {
	for (int i = len / 2; i > 0; i /= 2) {
		int k = 0;
		for (int j = i; j < len; j += 1) {
			// 插入排序
			T tmp = arr[j];
			for (k = j; k >= i && tmp < arr[k - i]; k -= i) {
				arr[k] = arr[k - i];
			}
			arr[k] = tmp;
		}
	}
}

template<class T>
void Algorithm::heap_sort(T* arr, int len) {
	// build heap
	for (int i = len / 2 - 1; i >= 0; i--) {
		//从第一个非叶子结点从下至上，从右至左调整结构
		insert_heap(arr, i, len);
	}

	for (int i = len-1; i > 0; i--) {
		swap(arr[0], arr[i]);//将堆顶元素与末尾元素进行交换
		insert_heap(arr, 0, i);
	}
}

template<class T>
T Algorithm::median3(T* arr, int from, int to) {
	int center = (from + to) / 2;
	if (arr[center] < arr[from])
		swap(arr[center], arr[from]);
	if (arr[to] < arr[from])
		swap(arr[to], arr[from]);
	if (arr[to] < arr[center])
		swap(arr[to], arr[center]);
	// place pivot at right -1;
	swap(arr[center], arr[to - 1]);
	return arr[to - 1];
}

template<class T>
void Algorithm::insert_heap(T* arr, int i, int to) {
	T tmp = arr[i];
	for (int j = i * 2 + 1; j < to; j = j * 2 + 1) {
		if (j+1 < to && arr[j] < arr[j + 1]) {
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

template<class T>
void Algorithm::merge(T* arr, int low, int mid, int high) {
	T *tmp = new T[high - low + 1];
	int start = 0, i = low, j = mid;
	while (i < mid && j <= high) {
		if (arr[i] <= arr[j]) {
			tmp[start++] = arr[i++];
		} else {
			tmp[start++] = arr[j++];
		}
	}
	while (i < mid) {
		tmp[start++] = arr[i++];
	}
	while (j <= high) {
		tmp[start++] = arr[j++];
	}
	// copy element
	for (int i = 0; i < high - low + 1; i++) {
		arr[low + i] = tmp[i];
	}
	delete[] tmp;
}

template<class T>
void Algorithm::merge_sort(T* arr, int low, int high) {
	if (low < high) {
		int mid = (low + high) / 2;
		merge_sort(arr, low, mid);
		merge_sort(arr, mid + 1, high);
		merge(arr, low, mid + 1, high);
	}
}

template<class T>
void Algorithm::merge_sort(T *arr, int len) {
	merge_sort(arr, 0, len - 1);
}