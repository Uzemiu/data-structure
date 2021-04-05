
#include <iostream>
#include <random>
#include <vector>
#include "Queens.h"
#include "RefinedQueens.h"

using namespace std;
void test_queen() {
	int size;
	cout << "What is the size of the board? " << flush;
	//cin >> size;
	size = 12;
	//Queens q(size);
	RefinedQueens q(size);
	q.solve();
	int i = 0;
}

int main(){

	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> dist(1, 30000);
	for (int i = 0; i < 20; i++) {
		cout << dist(gen) << endl;
	}

	test_queen();
}
