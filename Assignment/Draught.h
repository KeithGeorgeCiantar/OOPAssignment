#pragma once
#include <string>

#include "Piece.h"

class Draught : public Piece {
	public:
		Draught(unsigned int p, unsigned int x_arg, unsigned int y_arg) : Piece(p, x_arg, y_arg) {}
		~Draught();

		bool checkMove(unsigned int dest_x, unsigned int dest_y);
		bool checkEat(unsigned int dest_x, unsigned int dest_y);
		char getSymbol();
};