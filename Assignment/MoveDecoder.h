#pragma once
#include <string>

class MoveDecoder{
	private:
		std::string move;
	public:
		MoveDecoder(std::string m) : move(m) {}
		MoveDecoder();
		~MoveDecoder();

		bool isCorrectFormat();

		unsigned int getX(char arg_x);
		unsigned int getY(char arg_y);

		unsigned int getSourceX();
		unsigned int getSourceY();
		unsigned int getDestinationX();
		unsigned int getDestinationY();
};