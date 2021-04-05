#pragma once
#include "LinkedList.h"

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
};

