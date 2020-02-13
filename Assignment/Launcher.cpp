#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>
#include <stdlib.h>
#include <time.h>

#include "Board.h"
#include "MoveDecoder.h"
#include "PossibleEats.h"

unsigned int menu();

int main() {

	unsigned int choice;

	std::cout << "--- Welcome to Draughts! ---" << std::endl;
	choice = menu();

	Board game;
	unsigned int turn = 0;
	unsigned int win = 0;
	bool loaded = false;
	bool restart = false;

	do {
		if (choice == 1) {
			if (!loaded || restart) {
				std::cout << "Tossing coin..." << std::endl;

				srand((unsigned int) (time(NULL)));
				unsigned int start = (rand() % 2) + 1;

				std::cout << "Player " << start << " won the coin toss! They will start first." << std::endl;
				std::cout << std::endl;

				game.clearBoard();
				game.newGame();
				game.displayBoard();

				turn = start;
				restart = false;
			}

			bool stop = false;
			bool valid = false;
			bool can_eat = false;
			bool stay = false;
			std::string move;

			do {

				win = game.checkWin();

				if (win == 0) {
					std::cout << "Turn: Player " << turn << std::endl;

					do {
						std::cout << "Please enter your move: ";
						std::cin >> move;

						if (move == "0" && !can_eat) {
							std::cout << std::endl;
							choice = menu();

							if (choice == 1) {
								loaded = false;
								restart = true;
							} else {
								restart = false;
							}

							stop = true;
							valid = true;
						} else if (move == "0" && can_eat) {
							stay = true;
							valid = true;
							can_eat = false;
						} else {

							if (can_eat) {
								stay = false;
							} else {
								stay = true;
							}

							MoveDecoder md(move);

							if (md.isCorrectFormat()) {
								if ((md.getDestinationX() == (md.getSourceX() + 1)) || (md.getDestinationX() == (md.getSourceX() - 1))) {
									if (!can_eat) {
										if (game.checkMove(turn, md.getSourceX(), md.getSourceY(), md.getDestinationX(), md.getDestinationY())) {
											game.move(turn, md.getSourceX(), md.getSourceY(), md.getDestinationX(), md.getDestinationY());
											valid = true;
										} else {
											std::cout << "Invalid move! Please enter a valid move." << std::endl;
											valid = false;
										}
									} else {
										std::cout << "Invalid move! Please enter a valid move." << std::endl;
										valid = false;
									}
								} else if ((md.getDestinationX() == (md.getSourceX() + 2)) || (md.getDestinationX() == (md.getSourceX() - 2))) {
									if (game.checkEat(turn, md.getSourceX(), md.getSourceY(), md.getDestinationX(), md.getDestinationY())) {
										game.eat(turn, md.getSourceX(), md.getSourceY(), md.getDestinationX(), md.getDestinationY());
										valid = true;

										PossibleEats *pe = game.canEat(turn, md.getDestinationX(), md.getDestinationY());

										if (pe->bottom_left == true || pe->bottom_right == true || pe->top_left == true || pe->top_right == true) {
											std::cout << std::endl;
											std::cout << "You can eat again, press 0 to stay or enter a new set of coordinates." << std::endl;
											can_eat = true;
										} else {
											can_eat = false;
										}
									} else {
										std::cout << "Invalid move! Please enter a valid move." << std::endl;
										valid = false;
									}
								} else {
									std::cout << "Invalid move! Please enter a valid move." << std::endl;
									valid = false;
								}
							} else {
								std::cout << "Invalid move! Please enter a valid move." << std::endl;
								valid = false;
							}
						}
					} while (!valid);

					if (choice != 4 && choice != 3 && choice != 2 && !restart) {
						if ((move != "0" && !can_eat) || (stay && !can_eat)) {
							std::cout << std::endl;
							game.displayBoard();

							if (turn == 1) {
								turn = 2;
							} else {
								turn = 1;
							}
						}
					}

					if (can_eat) {
						std::cout << std::endl;
						game.displayBoard();
					}
				} else if (win == 1 || win == 2) {
					std::cout << "Player " << win << " won!! Congratulations!" << std::endl;
					std::cout << std::endl;
					stop = true;
					win = 0;
					loaded = false;
					choice = menu();
				}

			} while (!stop);

		} else if (choice == 2) {
			std::string file_name;
			bool valid = false;

			if (turn != 0) {
				do {
					file_name = "";
					std::cout << "Please enter the name of the save file (.txt not required) (no whitespaces at the beginning or end): ";
					std::getline(std::cin, file_name);

					//\ / : * ? " < > | 
					
					if (file_name.find('\\') == std::string::npos && file_name.find('/') == std::string::npos && file_name.find(':') == std::string::npos &&
						file_name.find('*') == std::string::npos && file_name.find('?') == std::string::npos && file_name.find('"') == std::string::npos &&
						file_name.find('<') == std::string::npos && file_name.find('>') == std::string::npos && file_name.find('|') == std::string::npos) {
						if (file_name != "" && file_name.at(0) != ' ' && file_name.at(file_name.length() - 1) != ' ') {
							file_name = file_name + ".txt";

							std::ofstream ofs(file_name, std::ofstream::out | std::ofstream::trunc);

							game.saveGame(ofs, turn);
							std::cout << "Game saved in: " << file_name << std::endl;
							std::cout << std::endl;
							game.clearBoard();
							valid = true;
						}
					} else {
						std::cout << "Invalid name! Please enter a valid name." << std::endl;
						valid = false;
					}
				} while (!valid);
			} else {
				std::cout << "Cannot save a game which has not been started!" << std::endl;
				std::cout << std::endl;
			}

			choice = menu();

		} else if (choice == 3) {
			game.clearBoard();

			std::string file_name;

			std::cout << "Please enter the name of the save file (.txt not required): ";
			std::getline(std::cin, file_name);

			file_name = file_name + ".txt";

			std::ifstream ifs(file_name);

			std::cout << std::endl;

			if (ifs) {
				game.clearBoard();
				turn = game.loadGame(ifs);
				if (turn != 0) {
					game.displayBoard();
					loaded = true;
					choice = 1;
				} else {
					game.clearBoard();
					std::cout << "Incorrect data in file!" << std::endl;
					std::cout << std::endl;
					choice = menu();
				}
			} else {
				std::cout << "File not found!" << std::endl;
				std::cout << std::endl;
				choice = menu();
			}

			ifs.close();
		}
		
		if (choice == 4) {
			game.clearBoard();
			std::cout << "Exiting game..." << std::endl;
			std::cout << std::endl;
		}
	} while (choice != 4);

	system("pause");

	return 0;
}

unsigned int menu() {
	unsigned int choice;

	std::cout << "1. Start new game." << std::endl;
	std::cout << "2. Save the current game." << std::endl;
	std::cout << "3. Load a saved game." << std::endl;
	std::cout << "4. Exit." << std::endl;
	std::cout << std::endl;

	do {
		std::cout << "Please enter a choice: ";
		std::cin >> choice;
		std::cin.ignore();
	} while (choice > 4 || choice < 1);

	std::cout << std::endl;

	return choice;
}