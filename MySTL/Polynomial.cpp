#include "LinkedList.cpp"
#include "Polynomial.h"

#include <iostream>
using namespace std;

void Polynomial::read() {
	clear();
	double coefficient;
	int last_exponent, exponent;
	bool first_term = true;
	cout << "Enter the coefficients and exponents for the polynomial, "
		<< "one pair per line. Exponents must be in descending order." << endl
		<< "Enter a coefficient of 0 or an exponent of 0 to terminate." << endl;
	do {
		cout << "coefficient? " << flush;
		cin >> coefficient;
		if (coefficient != 0.0) {
			cout << "exponent? " << flush;
			cin >> exponent;
			if ((!first_term && exponent >= last_exponent) || exponent < 0) {
				exponent = 0;
				cout << "Bad exponent: Polynomial terminates without its last term."
					<< endl;
			} else {
				Term new_term(exponent, coefficient);
				push(new_term);
				first_term = false;
			}
			last_exponent = exponent;
		}
	} while (coefficient != 0.0 && exponent != 0);
}

void Polynomial::print() const {
	Node<Term>* print_node = head;
	bool first_term = true;
	do {
		Term& print_term = print_node->ele;
		if (first_term) {
			first_term = false;
			if (print_term.coefficient < 0) cout << "- ";
		} else if (print_term.coefficient < 0) {
			cout << " - ";
		} else {
			cout << " + ";
		}
		double r = (print_term.coefficient >= 0)
			? print_term.coefficient : -(print_term.coefficient);
		if (r != 1) cout << r;
		if (print_term.degree > 1) cout << " X^" << print_term.degree;
		if (print_term.degree == 1) cout << " X";
		if (r == 1 && print_term.degree == 0) cout << " 1";
		print_node = print_node->next;
	} while (print_node != head);
	if (first_term)
		cout << "0";
	cout << endl;
}

void Polynomial::equals_sum(Polynomial p, Polynomial q) {
	clear();
	while (!p.empty() || !q.empty()) {
		if (p.degree() > q.degree()) {
			push(p.pop());
		} else if (q.degree() > p.degree()) {
			push(q.pop());
		} else {
			Term pt = p.pop(), qt = q.pop();
			if (pt.coefficient + qt.coefficient != 0) {
				push(Term(pt.degree,
						  pt.coefficient + qt.coefficient));
			}
		}
	}
}

void Polynomial::equals_difference(Polynomial p, Polynomial q) {
	// p - q
	clear();
	while (!p.empty() || !q.empty()) {
		if (p.degree() > q.degree()) {
			push(p.pop());
		} else if (q.degree() > p.degree()) {
			Term qt = q.pop();
			qt.coefficient = -qt.coefficient;
			push(qt);
		} else {
			Term pt = p.pop(), qt = q.pop();
			if (pt.coefficient - qt.coefficient != 0) {
				push(Term(pt.degree,
						  pt.coefficient - qt.coefficient));
			}
		}
	}
}

void Polynomial::equals_product(Polynomial p, Polynomial q) {
	throw "Not implemented";
}

bool Polynomial::equals_quotient(Polynomial p, Polynomial q) {
	throw "Not implemented";
}

int Polynomial::degree(){
	if (empty()) return -1;
	return peek().degree;
}

void Polynomial::mult_term(Term &t) {
	this->for_each([&t](Term& term) {
		term.coefficient *= t.coefficient;
		term.degree += t.degree;
			 });
}
