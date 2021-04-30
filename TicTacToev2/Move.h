#pragma once
class Move {
public:
	Move():Move::Move(0,0) {}
	Move(int r, int c):row(r), col(c) {}
	int row;
	int col;
};

