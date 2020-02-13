#include <string>

#include "King.h"

King::~King() {}

bool King::checkMove(unsigned int dest_x, unsigned int dest_y) {
	bool can_move = false;

	if (getPlayer() == 1 || getPlayer() == 2) {
		if (((dest_x == (getX() - 1)) || (dest_x == (getX() + 1))) && ((dest_y == (getY() - 1)) || (dest_y == (getY() + 1)))) {
			if ((dest_x >= 0 && dest_x <= 7) && (dest_y >= 0 && dest_y <= 7)) {
				if (((dest_x % 2) == 0) && ((dest_y % 2) == 0)) {
					can_move = true;
				} else if (((dest_x % 2) != 0) && ((dest_y % 2) != 0)) {
					can_move = true;
				}
			}
		}
	}

	return can_move;
}

bool King::checkEat(unsigned int dest_x, unsigned int dest_y) {
	bool can_eat = false;

	if (getPlayer() == 1 || getPlayer() == 2) {
		if (((dest_x == (getX() - 2)) || (dest_x == (getX() + 2))) && ((dest_y == (getY() - 2)) || (dest_y == (getY() + 2)))) {
			if ((dest_x >= 0 && dest_x <= 7) && (dest_y >= 0 && dest_y <= 7)) {
				if (((dest_x % 2) == 0) && ((dest_y % 2) == 0)) {
					can_eat = true;
				} else if (((dest_x % 2) != 0) && ((dest_y % 2) != 0)) {
					can_eat = true;
				}
			}
		}
	}

	return can_eat;
}

char King::getSymbol() {
	char s;

	if (getPlayer() == 1) {
		s = '#';
	} else if (getPlayer() == 2) {
		s = '*';
	}

	return s;
}