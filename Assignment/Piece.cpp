#include "Piece.h"

Piece::Piece(unsigned int p, unsigned int x_arg, unsigned int y_arg) : player(p), x(x_arg), y(y_arg) {
	if (player == 1) {
		colour = "Red";
	} else if (player == 2) {
		colour = "White";
	}
}