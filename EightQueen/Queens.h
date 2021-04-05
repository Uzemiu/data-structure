#pragma once
#include <vector>
using namespace std;
class Queens {
public:
	int board_size;
	int count;

	Queens(int size);

	bool is_solved(int row) const;
	void solve();
	void print();
	bool unguarded(int row, int col) const;
	void insert(int row, int col);
	void remove(int row, int col);
private:
	vector<vector<bool>> board;

	void solve(int n);
};

