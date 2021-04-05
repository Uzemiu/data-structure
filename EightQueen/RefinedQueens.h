#pragma once
#include <string>
using namespace std;
class RefinedQueens{
public:
	int board_size;
	int count;

	RefinedQueens(int size);

	void solve();
	void solve(int n);
	bool is_solved(int row) const;
	void print();
	bool unguarded(int row, int col) const;
	void insert(int row, int col);
	void remove(int row, int col);

private:
	static const int MAX_SIZE = 3000002;
	bool *col_free;
	bool *upward_free;
	bool *downward_free;
	int *queen_in_row;

};

