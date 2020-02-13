#include <string>
#include <ctype.h>

#include "MoveDecoder.h"

MoveDecoder::MoveDecoder() {}

MoveDecoder::~MoveDecoder() {}

bool MoveDecoder::isCorrectFormat() {
	bool correct = false;

	if (move.length() == 4) {
		if (isalpha(move.at(0)) && isdigit(move.at(1)) && isalpha(move.at(2)) && isdigit(move.at(3))) {
			if (((tolower(move.at(0)) >= 97) && (tolower(move.at(0)) <= 122)) && ((tolower(move.at(2)) >= 97) && (tolower(move.at(2)) <= 122))) {
				if (((move.at(1) >= 49) && (move.at(1) <= 56)) && ((move.at(3) >= 49) && (move.at(3) <= 56))) {
					correct = true;
				}
			}
		}
	}

	return correct;
}

unsigned int MoveDecoder::getX(char arg_x) {
	unsigned int x;

	switch (tolower(arg_x)) {
		case 'a':
			x = 0;
			break;
		case 'b':
			x = 1;
			break;
		case 'c':
			x = 2;
			break;
		case 'd':
			x = 3;
			break;
		case 'e':
			x = 4;
			break;
		case 'f':
			x = 5;
			break;
		case 'g':
			x = 6;
			break;
		case 'h':
			x = 7;
			break;
		default:
			x = 1000;
			break;
	}

	return x;
}

unsigned int MoveDecoder::getY(char arg_y) {
	unsigned int y;

	switch (arg_y) {
		case '1':
			y = 7;
			break;
		case '2':
			y = 6;
			break;
		case '3':
			y = 5;
			break;
		case '4':
			y = 4;
			break;
		case '5':
			y = 3;
			break;
		case '6':
			y = 2;
			break;
		case '7':
			y = 1;
			break;
		case '8':
			y = 0;
			break;
		default:
			y = 1000;
			break;
	}

	return y;
}

unsigned int MoveDecoder::getSourceX() {
	return getX(move.at(0));
}

unsigned int MoveDecoder::getSourceY() {
	return getY(move.at(1));
}

unsigned int MoveDecoder::getDestinationX() {
	return getX(move.at(2));
}

unsigned int MoveDecoder::getDestinationY() {
	return getY(move.at(3));
}