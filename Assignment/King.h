#pragma once
#include <string>

#include "Piece.h"

class King : public Piece {
	public:
		King(unsigned int p, unsigned int x_arg, unsigned int y_arg) : Piece(p, x_arg, y_arg) {}
		~King();

		bool checkMove(unsigned int dest_x, unsigned int dest_y);
		bool checkEat(unsigned int dest_x, unsigned int dest_y);
		char getSymbol();
};