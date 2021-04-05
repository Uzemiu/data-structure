#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <stack>
#include "MyDeque.cpp"
#include "LinkedList.cpp"
#include "Polynomial.h"
//#include "Joseph.cpp"

using namespace std;

void testlq() {
	/*
	LinkedList<int> cq;
	cq.insert(0, 999);
	cq.insert(1, 1111);
	cq.insert(2, 22222);
	cq.insert(1, 32215);
	//cq.pop_last();
	int i = cq.find(1111);
	int i2 = cq.find(123);
	cout << cq.get(i) << endl;
	cout << cq.get(i2) << endl;*/
}

void start_demonstration();


//-------------------

void introduction() {

}

void instructions() {
	cout << "[?] Read a Polynomial" << endl
		<< "[=] Return Top Polynomial" << endl
		<< "[+] Sum two Polynomial" << endl
		<< "[-] Difference two Polynomial" << endl
		<< "[*] Multi one Polynomial with a Term" << endl
		<< "[q] Quit." << endl;
}

bool do_command_(char command, LinkedList<Polynomial>& stack) {
	Polynomial p, q, r;
	switch (command) {
	case'?': 
		p.read();
		stack.push_last(p);
		cout << "New Polynomial was pushed into stack:" << endl;
		p.print();
		break;
	case'=':
		if (stack.empty()) {
			cout << "Empty stack" << endl;
		} else {
			stack.peek_last().print();
		}
		break;
	case'+': 
		if (stack.size() < 2) {
			cout << "Not enough polynomials in stack" << endl;
		} else {
			p = stack.pop_last();
			q = stack.pop_last();
			r.equals_sum(p, q);
			stack.push_last(r);
			cout << "New Polynomial was pushed into stack:" << endl;
			r.print();
		}
		break;
	case'-': 
		if (stack.size() < 2) {
			cout << "Not enough polynomials in stack" << endl;
		} else {
			p = stack.pop_last();
			q = stack.pop_last();
			r.equals_difference(q, p);
			stack.push_last(r);
			cout << "New Polynomial was pushed into stack:" << endl;
			r.print();
		}
		break;
	case'*':
		if (stack.empty()) {
			cout << "Empty stack" << endl;
		} else {
			Term t;
			cout << "coefficient? " << flush;
			cin >> t.coefficient;
			cout << "exponent? " << flush;
			cin >> t.degree;
			Polynomial& p = stack.peek_last();
			p.mult_term(t);
			cout << "New Polynomial is:" << endl;
			p.print();
		}
		break;
	case'q':
		cout << "Calculation finished." << endl;
		return false;
	default:
		cout << "Unknown command." << endl;
		break;
	}
	return true;
}

char get_command_() {
	char command;
	bool waiting = true;
	cout << "Select command and press <Enter>:";
	while (waiting) {
		cin >> command;
		command = tolower(command);
		if (command == '?' || command == '=' || command == '+' ||
			command == '-' || command == '*' || command == 'q')
			waiting = false;
		else {
			cout << "Please enter a valid command:" << endl;
			instructions();
		}
	}
	return command;
}

void test_polynomial() {

	LinkedList<Polynomial> stack;
	introduction();
	instructions();

	while (do_command_(get_command_(), stack));
}

int main() {
	test_polynomial();
}

