
#include <cstring>
#include <iostream>
#include "board.h"
#include "utils.h"

void board::setMenu() {
	for (int i = 0; i < MAX_Y; i++) {
		memcpy(currentBoard[i], manuBoard[i], MAX_X + 1);
	}
}
void board::setGame() {
	for (int i = 0; i < MAX_Y; i++) {
		memcpy(currentBoard[i], gameBoard[i], MAX_X + 1);
	}
}
void board::setGuide() {
	for (int i = 0; i < MAX_Y; i++) {
		memcpy(currentBoard[i], guideBoard[i], MAX_X + 1);
	}
}
void board::changePixel(Pos pos,char ch) {
	currentBoard[pos.y][pos.x] == ch;
}
void board::print() const {
	gotoxy(0, 0);
	for (int i = 0; i < MAX_Y - 1; i++) {
		std::cout << currentBoard[i] << '\n';
	}
	std::cout << currentBoard[MAX_Y - 1];
}
