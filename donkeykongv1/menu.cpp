
#include <cstring>
#include <iostream>
#include <windows.h>
#include <conio.h>
#include "utils.h"
#include "menu.h"
#include "board.h"
#include "mainGame.h"
#include <vector>
#include <filesystem>  // For working with the file system
#include <algorithm>   // For std::sort
#include <regex>       // For extracting numbers from filenames
#include <string>      // For string operations


// Method to initialize and handle the menu interactions
void Menu::start() {

	int screenNumber = 1;
	int currScore;
	board _board;       // Instance of the board to manage menu and guide displays
	mainGame _game;     // Instance of the game to handle gameplay logic

	std::vector<int> gameScores;// Vector to store all the gameScores

	std::vector<std::string> FileNames; // Vector to store file names
	int sumOfFiles = getAllBoardFileNames(FileNames); // Get all the file names in the screens folder
	
	_board.setMenu();   // Set the board to display the main menu
	_board.print();     // Print the menu to the console
	int i = 1;

	bool isRunning = true; // Flag to control the menu loop

	while (isRunning) {
		if (_kbhit()) { // Check if a key is pressed
			char key = _getch(); // Get the pressed key
			switch (key) {
			case '1': // Option 1: Start a new game
				if (sumOfFiles == 0) {
					_board.setNoFilesError(); // Set the board to display the no files error
					_board.print();           // Print the error message
					while (true) {
						if (_kbhit()) {
							char Esc = _getch();
							if (Esc == KeyCode::KEY_ESC) {
								break;
							}
						}
					}
					_board.setMenu();   // Reset to the menu after the game ends
					_board.print();     // Reprint the menu
					break;
				}
				currScore = _game.startGame(1,sumOfFiles);  // Start the game
				gameScores.push_back(currScore);
				_board.setMenu();   // Reset to the menu after the game ends
				_board.print();     // Reprint the menu
				break;

			case '2':
				_board.setChooseScreen();
				_board.print();
				screenNumber = _board.chooseScreen(FileNames,sumOfFiles);
				if (screenNumber != 0) {
					_game.startGame(screenNumber, sumOfFiles);
				}
				_board.setMenu();   // Reset to the menu after the game ends
				_board.print();     // Reprint the menu
				break;

			case '3':
				// Sort in descending order
				std::sort(gameScores.begin(), gameScores.end(), std::greater<int>());
				_board.setScoreBoard();
				_board.print();
				gotoxy(35, 7);
				for (int score : gameScores) {
					std::cout << i << ". " << score;
					gotoxy(35, 7 + i);
					i++;
				}
				i = 1;
				while (true) {
					if (_kbhit()) {
						char Esc = _getch();
						if (Esc == KeyCode::KEY_ESC) {
							break;
						}
					}
				}
				_board.setMenu();   // Reset to the menu after the game ends
				_board.print();     // Reprint the menu
				break;

			case KeyCode::KEY_ESC: // Escape key: Reset to the menu
				_board.setMenu();   // Reset the menu state
				_board.print();     // Reprint the menu
				break;

			case '8': // Option 8: Display the guide
				_board.setGuide();  // Set the board to display the guide
				_board.print();     // Print the guide
				while (true) {
					if (_kbhit()) {
						char Esc = _getch();
						if (Esc == KeyCode::KEY_ESC) {
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

// Method to get all the file names in the screens folder
int Menu::getAllBoardFileNames(std::vector<std::string>& vec_to_fill) {
	int count = 0;
	std::string folderPath = "screens"; // Path to the folder
	namespace fs = std::filesystem;

	// Collect all filenames with the .txt extension
	for (const auto& entry : fs::directory_iterator(folderPath)) {
		if (entry.is_regular_file() && entry.path().extension() == ".txt") {
			vec_to_fill.push_back(entry.path().filename().string());
			count++;
		}
	}

	// Natural sorting: extract numbers from filenames and sort accordingly
	std::sort(vec_to_fill.begin(), vec_to_fill.end(), [](const std::string& a, const std::string& b) {
		std::regex numberRegex(R"_(\d+)_");
		std::smatch matchA, matchB;
		std::string::const_iterator searchStartA(a.cbegin()), searchStartB(b.cbegin());

		if (std::regex_search(searchStartA, a.cend(), matchA, numberRegex) &&
			std::regex_search(searchStartB, b.cend(), matchB, numberRegex)) {
			return std::stoi(matchA.str()) < std::stoi(matchB.str());
		}
		return a < b; // Default to lexicographical if no numbers are found
		});

	return count;
}
