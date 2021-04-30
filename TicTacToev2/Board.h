#pragma once
#include "Move.h"
#include <iostream>

using namespace std;

class Board {
public:
	Board();
	bool done() const;
	void print() const;
	bool is_movement_legal(Move& move);
	void play(Move move);
	int the_winner() const;
	inline int current_player() {
		return (moves_done & 1) ? 2 : 1;
	}

	int squares[3][3];
	int moves_done;
};

