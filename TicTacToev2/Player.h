#pragma once
#include "Board.h"
#include <iostream>

using namespace std;

class Player {
public:
	Player(Board& board) :board(board) {}
	Move operator()() {
		Move move;
		cout << "Player's turn: " << endl;
		do {
			cout << "Row:";
			cin >> move.row;
			cout << "Column:";
			cin >> move.col;
		} while (!board.is_movement_legal(move));
		return move;
	}
private:
	Board& board;
};

