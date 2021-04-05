#pragma once
#include "Move.h"
#include <iostream>
#include <stack>

using namespace std;

class Board {
public:
	Board();
	bool done() const;
	void print() const;
	void instructions() const;
	bool better(int value, int old_value) const;
	bool is_movement_legal(Move& move);
	void play(Move try_it);
	int worst_case() const;
	int evaluate() const;
	int legal_moves(stack<Move> &moves) const;
	int the_winner() const;
private:
	int squares[3][3];
	int moves_done;
};

