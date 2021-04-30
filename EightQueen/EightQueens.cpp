#include <iostream>
#include <random>
#include <vector>
#include "Queens.h"
#include "RefinedQueens.h"

using namespace std;
void test_queen() {
	int size;
	cout << "What is the size of the board? " << flush;
	cin >> size;
	/*
	Queens q1(size);
	cout << "Queen v1:" << endl;
	q1.solve();
	cout << endl;*/
	cout << "RefinedQueue:" << endl;
	RefinedQueens q2(size);
	q2.solve();
}

int main(){

	test_queen();
	system("pause");
}
