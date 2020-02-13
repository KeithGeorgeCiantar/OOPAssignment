#pragma once
#include <string>

class MoveEncoder {
	private:
		unsigned int x;
		unsigned int y;
	public:
		MoveEncoder(unsigned int arg_x, unsigned int arg_y) : x(arg_x), y(arg_y) {}
		~MoveEncoder();

		std::string getBoardCoordinates();
};