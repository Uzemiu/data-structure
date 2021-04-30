#include "Board.h"

Board::Board() {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			squares[i][j] = 0;
		}
	}
	moves_done = 0;
}

bool Board::done() const {
	return moves_done == 9 || the_winner() > 0;
}

void Board::print() const {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++)
			 cout << " " << squares[i][j];
		 cout << " " << endl;
	}
	cout << endl;
}

bool Board::is_movement_legal(Move& move) {
	bool s = move.row >= 0 && move.row < 3
		&& move.col >= 0 && move.col < 3
		&& squares[move.row][move.col] == 0;
	if (!s) cout << "Illegal movement" << endl;
	return s;
}

void Board::play(Move move) {
	if (is_movement_legal(move)) {
		squares[move.row][move.col] = moves_done % 2 + 1;
		moves_done++;
	}
}

int Board::the_winner() const {
	int i;
	for (i = 0; i < 3; i++)
		if (squares[i][0] && squares[i][0] == squares[i][1]
			&& squares[i][0] == squares[i][2])
			return squares[i][0];
	for (i = 0; i < 3; i++)
		if (squares[0][i] && squares[0][i] == squares[1][i]
			&& squares[0][i] == squares[2][i])
			return squares[0][i];
	if (squares[0][0] && squares[0][0] == squares[1][1]
		&& squares[0][0] == squares[2][2])
		return squares[0][0];
	if (squares[0][2] && squares[0][2] == squares[1][1]
		&& squares[2][0] == squares[0][2])
		return squares[0][2];
	return 0;
}
