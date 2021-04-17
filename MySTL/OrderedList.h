#pragma once
#include "List.h"

struct Record {

};

class OrderedList : public List<Record> {

public:
	OrderedList();
	void insert();
};

