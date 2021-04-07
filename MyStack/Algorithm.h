#pragma once
#include "LinkedList.h"

#include <string>
using namespace std;

class Algorithm {
public:
	template<class T>
	static void insert_sort(T* arr, int from, int to);

	template<class T>
	static void quick_sort(T *arr, int from, int to);

	template<class T>
	static void selection_sort(T* arr, int from, int to);

	template<class T>
	static void shell_sort(T* arr, int from, int to);

	template<class T>
	static void heap_sort(T* arr, int to);

	template<class T>
	static void merge_sort(T* arr, int from, int to);

	static void radix_sort(string* arr, int to);

private:
	// for quick sort
	template<class T>
	static T median3(T* arr, int from, int to);

	// for heap sort
	template<class T>
	static void insert_heap(T *arr, int i, int len);

	// for radix sort
	const static int MAX_CHAR = 28;
	static int alphabetic_order(char c);
	static void rethread(LinkedList<string> bucket[28]);
};
