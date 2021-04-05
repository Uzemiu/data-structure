#include "RefinedQueens.h"
#include <iostream>

using namespace std;

string queen_solution_str = "";

RefinedQueens::RefinedQueens(int size) {
	ios::sync_with_stdio(false);
	board_size = size;
	count = 0;
	col_free = new bool[size];
	upward_free = new bool[size * 2 - 1];
	downward_free = new bool[size * 2 - 1];
	queen_in_row = new int[size];
}

void RefinedQueens::solve() {
	count = 0;
	memset(col_free, true, sizeof(col_free));
	memset(upward_free, true, sizeof(upward_free));
	memset(downward_free, true, sizeof(downward_free));
	solve(0);
	cout << queen_solution_str << endl;
	cout << "Total solutions: " << count << endl;
}

void RefinedQueens::solve(int row) {
	if (row >= board_size) {
		count++;
		print();
		return;
	}
	for (int col = 0; col < board_size; col++) {
		if (unguarded(row, col)) {
			insert(row, col);
			solve(row + 1);
			remove(row, col);
		}
	}
}

bool RefinedQueens::is_solved(int row) const {
	return row >= board_size;
}

void RefinedQueens::print() {
	for (int i = 0; i < board_size; i++) {
		queen_solution_str += to_string(queen_in_row[i]) + " ";
		//cout << queen_in_row[i] << " ";
	}
	queen_solution_str += "\n";
	//cout << endl;
}

bool RefinedQueens::unguarded(int row, int col) const {
	return col_free[col] 
		&& upward_free[row + col] 
		&& downward_free[row - col + board_size - 1];
}

void RefinedQueens::insert(int row, int col) {
	queen_in_row[row] = col;
	col_free[col] = false;
	upward_free[row + col] = false;
	downward_free[row - col + board_size - 1] = false;
}

void RefinedQueens::remove(int row, int col) {
	col_free[col] = true;
	upward_free[row + col] = true;
	downward_free[row - col + board_size - 1] = true;
}
