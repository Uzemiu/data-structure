#pragma once
#include <string>
#include <iostream>
#include "LinkedList.h"
using namespace std;

class Browser :public LinkedList<string>{
public:
	void visit(const string& page);
	bool forward();
	bool back();
	string current_page();

	static char get_command();
	static void run_test();

private:
	Node<string>* current;

};
