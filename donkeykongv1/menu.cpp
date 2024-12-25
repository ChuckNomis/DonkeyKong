#include <cstring>
#include <iostream>
#include <windows.h>
#include <conio.h>
#include "utils.h"
#include "menu.h"
#include "board.h"
#include "mainGame.h"

// Method to initialize and handle the menu interactions
void Menu::start() {
	board _board;       // Instance of the board to manage menu and guide displays
	mainGame _game;     // Instance of the game to handle gameplay logic

	_board.setMenu();   // Set the board to display the main menu
	_board.print();     // Print the menu to the console

	bool isRunning = true; // Flag to control the menu loop

	while (isRunning) {
		if (_kbhit()) { // Check if a key is pressed
			char key = _getch(); // Get the pressed key
			switch (key) {
			case '1': // Option 1: Start a new game
				_game.startGame();  // Start the game
				_board.setMenu();   // Reset to the menu after the game ends
				_board.print();     // Reprint the menu
				break;

			case 27: // Escape key: Reset to the menu
				_board.setMenu();   // Reset the menu state
				_board.print();     // Reprint the menu
				break;

			case '8': // Option 8: Display the guide
				_board.setGuide();  // Set the board to display the guide
				_board.print();     // Print the guide
				while (true) {
					if (_kbhit()) {
						char Esc = _getch();
						if (Esc == 27) {
							break;
						}
					}
				}
				_board.setMenu();   // Reset to the menu after the game ends
				_board.print();     // Reprint the menu
				break;

			case '9': // Option 9: Exit the menu
				isRunning = false;  // End the menu loop
				break;

			default: // Handle any invalid or unsupported inputs
				break;
			}
		}
	}
}