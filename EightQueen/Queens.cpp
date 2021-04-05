#include "Queens.h"
#include <iostream>

using namespace std;

Queens::Queens(int size) {
	board_size = size;
	count = 0;
	board = vector<vector<bool>>(size, vector<bool>(size, 0));
}

bool Queens::is_solved(int row) const {
	return row >= board_size;
}

void Queens::solve() {
	count = 0;
	solve(0);
	cout << "Total solutions: " << count << endl;
}

void Queens::solve(int n) {
	if (n >= board_size) {
		count++;
		print();
		return;
	}
	for (int column = 0; column < board_size; column++) {
		if (unguarded(n, column)) {
			board[n][column] = 1;
			solve(n + 1);
			board[n][column] = 0;
		}
	}
}

void Queens::print() {
	for (int i = 0; i < board_size; i++) {
		for (int j = 0; j < board_size; j++) {
			cout << board[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

bool Queens::unguarded(int row, int col) const {
	for (int x = 0; x < row; x++) {
		if (board[x][col]) return 0;
	}
	for (int x = row - 1, y = col - 1; x >= 0 && y >= 0; x--, y--) {
		if (board[x][y]) return 0;
	}
	for (int x = row - 1, y = col + 1; x >= 0 && y < board_size; x--, y++) {
		if (board[x][y]) return 0;
	}
	return 1;
}

void Queens::insert(int row, int col) {
	board[row][col] = 1;
}

void Queens::remove(int row, int col) {
	board[row][col] = 0;
}
