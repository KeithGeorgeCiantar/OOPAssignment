#include <iostream>
#include <string>

#include "Board.h"
#include "MoveDecoder.h"
#include "MoveEncoder.h"

Board::Board() {
	for (int j = 0; j < 8; j++) {
		for (int i = 0; i < 8; i++) {
			pieces[i][j] = nullptr;
		}
	}
}

Board::~Board() {
	clearBoard();
}

void Board::move(unsigned int player, int src_x, int src_y, int dest_x, int dest_y) {
	if (checkMove(player, src_x, src_y, dest_x, dest_y)) {
		if (checkPromotion(pieces[src_x][src_y]->getSymbol(), dest_y)) {
			pieces[dest_x][dest_y] = new King(player, dest_x, dest_y);
			delete pieces[src_x][src_y];
		} else {
			pieces[src_x][src_y]->setX(dest_x);
			pieces[src_x][src_y]->setY(dest_y);
			pieces[dest_x][dest_y] = pieces[src_x][src_y];			
		}

		pieces[src_x][src_y] = nullptr;
	}
}

void Board::eat(unsigned int player, int src_x, int src_y, int dest_x, int dest_y) {
	if (checkEat(player, src_x, src_y, dest_x, dest_y)) {
		if (checkPromotion(pieces[src_x][src_y]->getSymbol(), dest_y)) {
			pieces[dest_x][dest_y] = new King(player, dest_x, dest_y);
			delete pieces[src_x][src_y];
		} else {
			pieces[src_x][src_y]->setX(dest_x);
			pieces[src_x][src_y]->setY(dest_y);
			pieces[dest_x][dest_y] = pieces[src_x][src_y];
		}

		pieces[src_x][src_y] = nullptr;

		if ((dest_x == (src_x - 2)) && (dest_y == (src_y - 2))) {
			delete pieces[src_x - 1][src_y - 1];
			pieces[src_x - 1][src_y - 1] = nullptr;
		} else if ((dest_x == (src_x + 2)) && (dest_y == (src_y - 2))) {
			delete pieces[src_x + 1][src_y - 1];
			pieces[src_x + 1][src_y - 1] = nullptr;
		} else if ((dest_x == (src_x + 2)) && (dest_y == (src_y + 2))) {
			delete pieces[src_x + 1][src_y + 1];
			pieces[src_x + 1][src_y + 1] = nullptr;
		} else if ((dest_x == (src_x - 2)) && (dest_y == (src_y + 2))) {
			delete pieces[src_x - 1][src_y + 1];
			pieces[src_x - 1][src_y + 1] = nullptr;
		}
	}
}

bool Board::checkPromotion(char symbol, unsigned int dest_y) {
	bool can_promote = false;

	if (symbol == 'o' && dest_y == 0) {
		can_promote = true;
	} else if (symbol == 'x' && dest_y == 7) {
		can_promote = true;
	}

	return can_promote;
}

bool Board::checkMove(unsigned int player, int src_x, int src_y, int dest_x, int dest_y) {
	bool can_move = false;

	if (player == 1 || player == 2) {
		if ((((src_x % 2) == 0) && ((src_y % 2) == 0)) || (((src_x % 2) != 0) && ((src_y % 2) != 0))) {
			if ((((dest_x % 2) == 0) && ((dest_y % 2) == 0)) || (((dest_x % 2) != 0) && ((dest_y % 2) != 0))) {
				if (((src_x >= 0) && (src_x <= 7)) && ((src_y >= 0) && (src_y <= 7)) && ((dest_x >= 0) && (dest_x <= 7)) && ((dest_y >= 0) && (dest_y <= 7))) {
					if (pieces[src_x][src_y] != nullptr) {
						if (pieces[src_x][src_y]->getPlayer() == player) {
							if (pieces[dest_x][dest_y] == nullptr) {
								if (pieces[src_x][src_y]->checkMove(dest_x, dest_y)) {
									can_move = true;
								}
							}
						}
					}
				}
			}
		}
	}

	return can_move;
}

PossibleEats* Board::canEat(unsigned int player, int src_x, int src_y) {
	bool top_left = false;
	bool top_right = false;
	bool bottom_left = false;
	bool bottom_right = false;

	if (player == 1) {
		if (((src_x >= 0) && (src_x <= 7)) && ((src_y >= 0) && (src_y <= 7))) {
			if ((((src_x % 2) == 0) && ((src_y % 2) == 0)) || (((src_x % 2) != 0) && ((src_y % 2) != 0))) {
				if (pieces[src_x][src_y] != nullptr) {
					if (pieces[src_x][src_y]->getPlayer() == player) {
						if (pieces[src_x][src_y]->getSymbol() == 'o') {
							if (((src_x - 1) >= 0) && ((src_y - 1) >= 0)) {
								if (pieces[src_x - 1][src_y - 1] != nullptr) {
									if (pieces[src_x - 1][src_y - 1]->getPlayer() != player) {
										if (((src_x - 2) >= 0) && ((src_y - 2) >= 0)) {
											if (pieces[src_x - 2][src_y - 2] == nullptr) {
												if (pieces[src_x][src_y]->checkEat(src_x - 2, src_y - 2)) {
													top_left = true;
												}
											}
										}
									}
								}
							}

							if (((src_x + 1) <= 7) && ((src_y - 1) >= 0)) {
								if (pieces[src_x + 1][src_y - 1] != nullptr) {
									if (pieces[src_x + 1][src_y - 1]->getPlayer() != player) {
										if (((src_x + 2) <= 7) && ((src_y - 2) >= 0)) {
											if (pieces[src_x + 2][src_y - 2] == nullptr) {
												if (pieces[src_x][src_y]->checkEat(src_x + 2, src_y - 2)) {
													top_right = true;
												}
											}
										}
									}
								}
							}
						} else if (pieces[src_x][src_y]->getSymbol() == '#') {
							if (((src_x - 1) >= 0) && ((src_y - 1) >= 0)) {
								if (pieces[src_x - 1][src_y - 1] != nullptr) {
									if (pieces[src_x - 1][src_y - 1]->getPlayer() != player) {
										if (((src_x - 2) >= 0) && ((src_y - 2) >= 0)) {
											if (pieces[src_x - 2][src_y - 2] == nullptr) {
												if (pieces[src_x][src_y]->checkEat(src_x - 2, src_y - 2)) {
													top_left = true;
												}
											}
										}
									}
								}
							}

							if (((src_x + 1) <= 7) && ((src_y - 1) >= 0)) {
								if (pieces[src_x + 1][src_y - 1] != nullptr) {
									if (pieces[src_x + 1][src_y - 1]->getPlayer() != player) {
										if (((src_x + 2) <= 7) && ((src_y - 2) >= 0)) {
											if (pieces[src_x + 2][src_y - 2] == nullptr) {
												if (pieces[src_x][src_y]->checkEat(src_x + 2, src_y - 2)) {
													top_right = true;
												}
											}
										}
									}
								}
							}

							if (((src_x + 1) <= 7) && ((src_y + 1) <= 7)) {
								if (pieces[src_x + 1][src_y + 1] != nullptr) {
									if (pieces[src_x + 1][src_y + 1]->getPlayer() != player) {
										if (((src_x + 2) <= 7) && ((src_y + 2) <= 7)) {
											if (pieces[src_x + 2][src_y + 2] == nullptr) {
												if (pieces[src_x][src_y]->checkEat(src_x + 2, src_y + 2)) {
													bottom_right = true;
												}
											}
										}
									}
								}
							}

							if (((src_x - 1) >= 0) && ((src_y + 1) <= 7)) {
								if (pieces[src_x - 1][src_y + 1] != nullptr) {
									if (pieces[src_x - 1][src_y + 1]->getPlayer() != player) {
										if (((src_x - 2) >= 0) && ((src_y + 2) <= 7)) {
											if (pieces[src_x - 2][src_y + 2] == nullptr) {
												if (pieces[src_x][src_y]->checkEat(src_x - 2, src_y + 2)) {
													bottom_left = true;
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
	} else if (player == 2) {
		if (((src_x >= 0) && (src_x <= 7)) && ((src_y >= 0) && (src_y <= 7))) {
			if ((((src_x % 2) == 0) && ((src_y % 2) == 0)) || (((src_x % 2) != 0) && ((src_y % 2) != 0))) {
				if (pieces[src_x][src_y] != nullptr) {
					if (pieces[src_x][src_y]->getPlayer() == player) {
						if (pieces[src_x][src_y]->getSymbol() == 'x') {
							if (((src_x - 1) >= 0) && ((src_y + 1) <= 7)) {
								if (pieces[src_x - 1][src_y + 1] != nullptr) {
									if (pieces[src_x - 1][src_y + 1]->getPlayer() != player) {
										if (((src_x - 2) >= 0) && ((src_y + 2) <= 7)) {
											if (pieces[src_x - 2][src_y + 2] == nullptr) {
												if (pieces[src_x][src_y]->checkEat(src_x - 2, src_y + 2)) {
													bottom_left = true;
												}
											}
										}
									}
								}
							}

							if (((src_x + 1) <= 7) && ((src_y + 1) <= 7)) {
								if (pieces[src_x + 1][src_y + 1] != nullptr) {
									if (pieces[src_x + 1][src_y + 1]->getPlayer() != player) {
										if (((src_x + 2) <= 7) && ((src_y + 2) <= 7)) {
											if (pieces[src_x + 2][src_y + 2] == nullptr) {
												if (pieces[src_x][src_y]->checkEat(src_x + 2, src_y + 2)) {
													bottom_right = true;
												}
											}
										}
									}
								}
							}
						} else if (pieces[src_x][src_y]->getSymbol() == '*') {
							if (((src_x - 1) >= 0) && ((src_y - 1) >= 0)) {
								if (pieces[src_x - 1][src_y - 1] != nullptr) {
									if (pieces[src_x - 1][src_y - 1]->getPlayer() != player) {
										if (((src_x - 2) >= 0) && ((src_y - 2) >= 0)) {
											if (pieces[src_x - 2][src_y - 2] == nullptr) {
												if (pieces[src_x][src_y]->checkEat(src_x - 2, src_y - 2)) {
													top_left = true;
												}
											}
										}
									}
								}
							}

							if (((src_x + 1) <= 7) && ((src_y - 1) >= 0)) {
								if (pieces[src_x + 1][src_y - 1] != nullptr) {
									if (pieces[src_x + 1][src_y - 1]->getPlayer() != player) {
										if (((src_x + 2) <= 7) && ((src_y - 2) >= 0)) {
											if (pieces[src_x + 2][src_y - 2] == nullptr) {
												if (pieces[src_x][src_y]->checkEat(src_x + 2, src_y - 2)) {
													top_right = true;
												}
											}
										}
									}
								}
							}

							if (((src_x + 1) <= 7) && ((src_y + 1) <= 7)) {
								if (pieces[src_x + 1][src_y + 1] != nullptr) {
									if (pieces[src_x + 1][src_y + 1]->getPlayer() != player) {
										if (((src_x + 2) <= 7) && ((src_y + 2) <= 7)) {
											if (pieces[src_x + 2][src_y + 2] == nullptr) {
												if (pieces[src_x][src_y]->checkEat(src_x + 2, src_y + 2)) {
													bottom_right = true;
												}
											}
										}
									}
								}
							}

							if (((src_x - 1) >= 0) && ((src_y + 1) <= 7)) {
								if (pieces[src_x - 1][src_y + 1] != nullptr) {
									if (pieces[src_x - 1][src_y + 1]->getPlayer() != player) {
										if (((src_x - 2) >= 0) && ((src_y + 2) <= 7)) {
											if (pieces[src_x - 2][src_y + 2] == nullptr) {
												if (pieces[src_x][src_y]->checkEat(src_x - 2, src_y + 2)) {
													bottom_left = true;
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}

	return new PossibleEats(top_left, top_right, bottom_left, bottom_right);
}

bool Board::checkEat(unsigned int player, int src_x, int src_y, int dest_x, int dest_y) {
	bool can_eat = false;
	PossibleEats *pe = canEat(player, src_x, src_y);
	
	if ((((src_x % 2) == 0) && ((src_y % 2) == 0)) || (((src_x % 2) != 0) && ((src_y % 2) != 0))) {
		if ((((dest_x % 2) == 0) && ((dest_y % 2) == 0)) || (((dest_x % 2) != 0) && ((dest_y % 2) != 0))) {
			if (((src_x >= 0) && (src_x <= 7)) && ((src_y >= 0) && (src_y <= 7)) && ((dest_x >= 0) && (dest_x <= 7)) && ((dest_y >= 0) && (dest_y <= 7))) {
				if ((dest_x == (src_x - 2)) && (dest_y == (src_y - 2))) {
					if (pe->top_left == true) {
						can_eat = true;
					}
				} else if ((dest_x == (src_x + 2)) && (dest_y == (src_y - 2))) {
					if (pe->top_right == true) {
						can_eat = true;
					}
				} else if ((dest_x == (src_x + 2)) && (dest_y == (src_y + 2))) {
					if (pe->bottom_right == true) {
						can_eat = true;
					}
				} else if ((dest_x == (src_x - 2)) && (dest_y == (src_y + 2))) {
					if (pe->bottom_left == true) {
						can_eat = true;
					}
				}
			}
		}
	}

	return can_eat;
}

unsigned int Board::checkWin() {
	unsigned int player_1_pieces = 0;
	unsigned int player_2_pieces = 0;

	for (int j = 0; j < 8; j++) {
		for (int i = 0; i < 8; i++) {
			if (pieces[i][j] != nullptr) {
				if (pieces[i][j]->getPlayer() == 1) {
					player_1_pieces++;
				} else {
					player_2_pieces++;
				}
			}
		}
	}

	if (player_1_pieces == 0) {
		return 2;
	} else if (player_2_pieces == 0){
		return 1;
	} else {
		return 0;
	}
}

void Board::displayBoard() {
	std::cout << "    Player 2 (White)" << std::endl;
	std::cout << std::endl;
	std::cout << "    A B C D E F G H" << std::endl;
	std::cout << std::endl;

	for (int j = 0; j < 8; j++) {
		std::cout << std::to_string(8 - j) + "   ";
		for (int i = 0; i < 8; i++) {
			if (pieces[i][j] == nullptr) {
				if ((((i % 2) == 0) && ((j % 2) == 0)) || (((i % 2) != 0) && ((j % 2) != 0))) {
					std::cout << " ";
				} else if ((((i % 2) == 0) && ((j % 2) != 0)) || (((i % 2) != 0) && ((j % 2) == 0))) {
					std::cout << ".";
				}
			} else {
				std::cout << pieces[i][j]->getSymbol();
			}
			std::cout << " ";
		}
		std::cout << "  " + std::to_string(8 - j) << std::endl;
	}

	std::cout << std::endl;
	std::cout << "    A B C D E F G H" << std::endl;
	std::cout << std::endl;
	std::cout << "    Player 1 (Red)" << std::endl;
	std::cout << std::endl;
}

void Board::clearBoard() {
	for (int j = 0; j < 8; j++) {
		for (int i = 0; i < 8; i++) {
			if (pieces[i][j] != nullptr) {
				delete pieces[i][j];
			}
			pieces[i][j] = nullptr;
		}
	}
}

void Board::newGame() {
	for (int j = 0; j < 3; j++) {
		for (int i = 0; i < 8; i++) {
			if (((i % 2) == 0) && ((j % 2) == 0)) {
				pieces[i][j] = new Draught(2, i, j);
			} else if (((i % 2) != 0) && ((j % 2) != 0)) {
				pieces[i][j] = new Draught(2, i, j);
			}
		}
	}

	for (int j = 5; j < 8; j++) {
		for (int i = 0; i < 8; i++) {
			if (((i % 2) == 0) && ((j % 2) == 0)) {
				pieces[i][j] = new Draught(1, i, j);
			} else if (((i % 2) != 0) && ((j % 2) != 0)) {
				pieces[i][j] = new Draught(1, i, j);
			}
		}
	}
}

void Board::saveGame(std::ostream &outputStream, unsigned int next_turn) {
	std::string colour;

	if (next_turn == 1) {
		colour = "Red";
	} else {
		colour = "White";
	}
	
	outputStream << "Next: " << colour << std::endl;

	for (int j = 0; j < 8; j++) {
		for (int i = 0; i < 8; i++) {
			if (pieces[i][j] != nullptr) {
				MoveEncoder me(i, j);
				outputStream << pieces[i][j]->getSymbol() << ":" << me.getBoardCoordinates() << std::endl;
			}
		}
	}
}

unsigned int Board::loadGame(std::istream &inputStream) {
	std::string first_line;
	unsigned int next_player = 0;;
	unsigned int player_1_pieces = 0;
	unsigned int player_2_pieces = 0;

	std::getline(inputStream, first_line);
	
	if (first_line != "") {
		if (tolower(first_line.at(6)) == 'r' && tolower(first_line.at(7)) == 'e' && tolower(first_line.at(8)) == 'd') {
			next_player = 1;
		} else if (tolower(first_line.at(6)) == 'w' && tolower(first_line.at(7)) == 'h' && tolower(first_line.at(8)) == 'i' && tolower(first_line.at(9)) == 't' && tolower(first_line.at(10)) == 'e') {
			next_player = 2;
		} else {
			next_player = 0;
		}
	} else {
		next_player = 0;
	}

	while (inputStream) {
		std::string line;
		std::getline(inputStream, line);

		unsigned int x;
		unsigned int y;
		unsigned int player;

		if (line != "") {
			MoveDecoder md;
			x = md.getX(line.at(2));
			y = md.getY(line.at(3));

			if ((x >= 0 && x <= 7) && (y >= 0 && y <= 7)) {
				if ((((x % 2) == 0) && ((y % 2) == 0)) || (((x % 2) != 0) && ((y % 2) != 0))) {
					if (line.at(0) == 'o') {
						player = 1;
						if (pieces[x][y] == nullptr) {
							if (y != 0) {
								pieces[x][y] = new Draught(player, x, y);
							} else {
								pieces[x][y] = new King(player, x, y);
							}
							player_1_pieces++;
						}
					} else if (line.at(0) == '#') {
						player = 1;
						if (pieces[x][y] == nullptr) {
							pieces[x][y] = new King(player, x, y);
							player_1_pieces++;
						}
					} else if (line.at(0) == 'x') {
						player = 2;
						if (pieces[x][y] == nullptr) {
							if (y != 7) {
								pieces[x][y] = new Draught(player, x, y);
							} else {
								pieces[x][y] = new King(player, x, y);
							}
							player_2_pieces++;
						}
					} else if (line.at(0) == '*') {
						player = 2;
						if (pieces[x][y] == nullptr) {
							pieces[x][y] = new King(player, x, y);
							player_2_pieces++;
						}
					}
				}
			}
		}
	}

	if (((player_1_pieces > 12) || (player_2_pieces > 12)) || ((player_1_pieces == 0) && (player_2_pieces == 0))) {
		next_player = 0;
	}

	return next_player;
}