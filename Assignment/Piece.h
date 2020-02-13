#pragma once
#include <string>

class Piece {
	private:
		const unsigned int player;
		std::string colour = "";
		unsigned int x;
		unsigned int y;
	public:
		Piece(unsigned int p, unsigned int x_arg, unsigned int y_arg);
		virtual ~Piece() = default;
		
		unsigned int getX() const { return x; }
		void setX(unsigned int new_x) { x = new_x; }

		unsigned int getY() const { return y; }
		void setY(unsigned int new_y) { y = new_y; }

		unsigned int getPlayer() const { return player; }
		
		std::string getColour() const { return colour; }

		virtual bool checkMove(unsigned int dest_x, unsigned int dest_y) = 0;
		virtual bool checkEat(unsigned int dest_x, unsigned int dest_y) = 0;
		virtual char getSymbol() = 0;
};