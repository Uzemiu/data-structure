#pragma once
#include "Board.h"
#include "Computer.h"
#include "Player.h"

class Game {
public:
	template<class PLAYER1, class PLAYER2>
	void start(PLAYER1 p1, PLAYER2 p2) {
		for (; !board.done();) {
			board.play((board.current_player() % 2) ? p1() : p2());
			board.print();
		}
		int winner = board.the_winner();
		if (winner == 1)
			cout << "Player1 won." << endl;
		else if (winner == 2)
			cout << "Player2 won." << endl;
		else
			cout << "Draw." << endl;
	}

	void start() {
		board = Board();
		Computer com(board);
		Player pla(board);
		start(pla,com);
	}

private:
	Board board;
	
};

