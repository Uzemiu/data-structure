#include <iostream>
#include <algorithm>
#include <time.h>
#include "Board.h"
#include "Move.h"

using namespace std;

Board game;
int i = 9;


int look_ahead(const Board&game,int depth, Move&recommended) {
	if (game.done() || depth == 0) {
		return game.evaluate();
	}
	stack<Move> moves;
	game.legal_moves(moves);
	int value, best_value = game.worst_case();
	while (!moves.empty()) {
		Move try_it = moves.top(), reply;
		Board new_game = game;
		new_game.play(try_it);
		value = look_ahead(new_game, depth - 1,reply);
		if (game.better(value, best_value)) {
			best_value = value;
			recommended = try_it;
		} else if (value == best_value) {
			time_t current = time(NULL);
			if (current & 1) {
				recommended = try_it;
			}
		}
		moves.pop();
	}
	return best_value;
}

template<class DO_MOVE>
void start_game(DO_MOVE player1, DO_MOVE player2) {
	game = Board();
	i = 9;
	game.instructions();

	for (; !game.done(); i--) {
		game.play(i % 2 ? player1() : player2());
		game.print();
	}
	int winner = game.the_winner();
	if (winner == 1)
		cout << "Player1 won." << endl;
	else if (winner == 2)
		cout << "Player2 won." << endl;
	else
		cout << "Draw." << endl;
}

Move computer() {
	cout << "Computer's turn:" << endl;
	if (i == 9) {
		int t = time(NULL) % 9;
		return Move(t % 3, t / 3);
	}
	Move recommend;
	look_ahead(game, i, recommend);
	return recommend;
}

Move human() {
	Move move;
	cout << "Player's turn: " << endl;
	do {
		cout << "Row:";
		cin >> move.row;
		cout << "Column:";
		cin >> move.col;
	} while (!game.is_movement_legal(move));
	return move;
}

void start_game() {
	start_game(human, computer);
}

int main(){
	start_game();
}