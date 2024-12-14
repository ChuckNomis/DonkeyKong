
#include <cstring>
#include <iostream>
#include <windows.h>
#include <conio.h>
#include "utils.h"
#include "menu.h"
#include "board.h"
#include "mainGame.h"
void Menu::start() {
	board _board;
	mainGame _game;
	_board.setMenu();
	_board.print();
	bool isRunning = true; // Control the loop
	while (isRunning) {
		if (_kbhit()) { // Check if a key is pressed
			char key = _getch();
			switch (key) {
			case '1': // Start a new game
				_game.startGame();
				_board.setMenu(); // Return to menu after game ends
				_board.print();
				break;
			case 27:// Escape key: Reset menu
				_board.setMenu();
				_board.print();
				break;
			case '8':// Show guide
				_board.setGuide();
				_board.print();
				break;
			case '9':// Exit the menu
				isRunning = false;
				break;
			default:
				break;
			}
		}
	}
}