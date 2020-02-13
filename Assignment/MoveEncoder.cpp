#include "MoveEncoder.h"

MoveEncoder::~MoveEncoder() {}

std::string MoveEncoder::getBoardCoordinates() {
	std::string str_x;
	std::string str_y;
	std::string full_coordinate;

	switch (x) {
		case 0:
			str_x = "a";
			break;
		case 1:
			str_x = "b";
			break;
		case 2:
			str_x = "c";
			break;
		case 3:
			str_x = "d";
			break;
		case 4:
			str_x = "e";
			break;
		case 5:
			str_x = "f";
			break;
		case 6:
			str_x = "g";
			break;
		case 7:
			str_x = "h";
			break;
	}

	switch (y) {
		case 0:
			str_y = "8";
			break;
		case 1:
			str_y = "7";
			break;
		case 2:
			str_y = "6";
			break;
		case 3:
			str_y = "5";
			break;
		case 4:
			str_y = "4";
			break;
		case 5:
			str_y = "3";
			break;
		case 6:
			str_y = "2";
			break;
		case 7:
			str_y = "1";
			break;
	}

	full_coordinate = str_x + str_y;

	return full_coordinate;
}
