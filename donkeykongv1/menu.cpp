
#include <cstring>
#include <iostream>
#include <windows.h>
#include <conio.h>
#include "utils.h"
#include "menu.h"
#include "board.h"
#include "mainGame.h"
void Menu::start() {
	board board;
	mainGame game;
	board.setMenu();
	board.print();
	bool isRunning = true; // Control the loop
	while (isRunning) {
		if (_kbhit()) { // Check if a key is pressed
			char key = _getch();
			switch (key) {
			case '1': // Start a new game
				game.startGame();
				board.setMenu(); // Return to menu after game ends
				board.print();
				break;
			case 27:// Escape key: Reset menu
				board.setMenu();
				board.print();
				break;
			case '8':// Show guide
				board.setGuide();
				board.print();
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