#pragma once
#include <iostream>

#include "Piece.h"
#include "King.h"
#include "Draught.h"
#include "PossibleEats.h"

#include "MoveDecoder.h"
#include "MoveEncoder.h"

class Board {
	private:
		Piece* pieces[8][8];
	public:
		Board();
		~Board();

		void move(unsigned int player, int src_x, int src_y, int dest_x, int dest_y);
		void eat(unsigned int player, int src_x, int src_y, int dest_x, int dest_y);

		bool checkPromotion(char symbol, unsigned int dest_x);

		bool checkMove(unsigned int player, int src_x, int src_y, int dest_x, int dest_y);

		PossibleEats* canEat(unsigned int player, int src_x, int src_y);
		bool checkEat(unsigned int player, int src_x, int src_y, int dest_x, int dest_y);

		unsigned int checkWin();

		void displayBoard();
		void clearBoard();
		void newGame();

		void saveGame(std::ostream &outputStream, unsigned int next_turn);
		unsigned int loadGame(std::istream &inputStream);
};