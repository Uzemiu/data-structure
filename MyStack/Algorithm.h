#pragma once
#include <vector>
using namespace std;
class Algorithm {
public:
	template<class T>
	static void insert_sort(T* arr, int from, int to);

	template<class T>
	static void quick_sort(T *arr, int from, int to);

	template<class T>
	static void heap_sort(T* arr, int to);

	template<class T>
	static void merge_sort(T* arr, int from, int to);

	template<class T>
	static void radix_sort(T* arr, int from, int to);

private:
	template<class T>
	static T median3(T* arr, int from, int to);

	template<class T>
	static void insert_heap(T *arr, int i, int len);
};
