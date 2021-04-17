#pragma once
#include "LinkedList.h"
#include "String.h"

template<class T>
class SortableList : public LinkedList<T> {

public:
	void radix_sort();

private:
	int alphabetic_order(char c);

};

