#pragma once
#include "Move.h"
#include <iostream>
#include <stack>

using namespace std;

class Board {
public:
	static const int DIFFICULTY_ABNORMAL = 9;
	static const int DIFFICULTY_INSANE = 5;
	static const int DIFFICULTY_NORMAL = 0;
	// 0~10 越低电脑越正常
	int level;

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

