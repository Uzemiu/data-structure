#pragma once
#include "LinkedList.h"

#include <iostream>

using namespace std;

struct Term {
	int degree;
	double coefficient;
	Term() : degree(0), coefficient(0.0) {}
	Term(int degree, double coefficient) : degree(degree), coefficient(coefficient) {}
};

class Polynomial: public LinkedList<Term>{
public:
	void read();
	void print() const;
	void equals_sum(Polynomial p, Polynomial q);
	void equals_difference(Polynomial p, Polynomial q);
	void equals_product(Polynomial p, Polynomial q);
	bool equals_quotient(Polynomial p, Polynomial q);
	void mult_term(Term &t);
	int degree();


	static void introduction() {
		cout << "This is Polynomial" << endl;
	}

	static void instructions() {
		cout << "[?] Read a Polynomial" << endl
			<< "[=] Return Top Polynomial" << endl
			<< "[+] Sum two Polynomial" << endl
			<< "[-] Difference two Polynomial" << endl
			<< "[*] Multi one Polynomial with a Term" << endl
			<< "[q] Quit." << endl;
	}

	static bool do_command(char command, LinkedList<Polynomial>& stack) {
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

	static char get_command() {
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

	static void test_polynomial() {
		LinkedList<Polynomial> stack;
		introduction();
		instructions();
		while (do_command(get_command(), stack));
	}

};

