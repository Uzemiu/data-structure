#pragma once
#include "Board.h"

class Computer {
public:
	Computer(Board& board) :board(board) {}
	Move operator()() {
		Move move;
		look_ahead(DEPTH, -10, 10, move);
		return move;
	}
private:
	Board& board;
	int DEPTH = 7;
	const int PLAYER1 = 1; // MAX
	const int PLAYER2 = 2; // MIN

	int evaluate() {
		int winner = board.the_winner();
		if (winner == PLAYER1) return 10;
		else if (winner == PLAYER2) return -10;
		else return 0;
	}

	int look_ahead(int depth, int alpha, int beta, Move& best) {
		if (board.done() || depth == 0) {
			return evaluate();
		}
		int player = board.current_player();
		if (player == PLAYER1) {
			// 取极大值节点
			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 3; j++) {
					int value = alpha;
					if (board.squares[i][j] == 0) {
						board.squares[i][j] = player;
						board.moves_done++;
						int score = look_ahead(depth - 1, alpha, beta, best);
						board.moves_done--; 
						board.squares[i][j] = 0;
						if (score > value) {
							best.row = i;
							best.col = j;
							value = score;
							if (value >= beta) {
								return beta;
							}
						}
					}
				}
			}
			return alpha;
		} else {
			// 取极小值节点
			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 3; j++) {
					int value = beta;
					if (board.squares[i][j] == 0) {
						board.squares[i][j] = player;
						board.moves_done++;
						int score = look_ahead(depth - 1, alpha, beta, best);
						board.moves_done--;
						board.squares[i][j] = 0;
						if (score < value) {
							best.row = i;
							best.col = j;
							value = score;
							if (alpha >= value) {
								return alpha;
							}
						}
					}
				}
			}
			return beta;
		}
	}
};
