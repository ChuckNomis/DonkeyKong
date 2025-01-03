#include <cstring>
#include <iostream>
#include "board.h"
#include "utils.h"
#include <fstream>
#include <string>
#include <sstream>

// Function to set the board to the menu state
void board::setMenu() {
    // Loop through all rows and copy the menu board to the current board
    for (int i = 0; i < MAX_Y; i++) {
        memcpy(currentBoard[i], manuBoard[i], MAX_X + 1);  // Copy each row with an additional null terminator
    }
}

bool board::isScreenOk(int screenNumber) {
	std::ostringstream filenameStream;
	filenameStream << "dkong_" << screenNumber << ".screen.txt";
	std::string filename = filenameStream.str();
    std::ifstream file("screens/" + filename);
    if (file.is_open()) {
        Pos donkeyKongPos = searchChar('&');
        if (donkeyKongPos.x == -1 || donkeyKongPos.y == -1) {
            return false;
        }
        Pos marioPos = searchChar('@');
        if (marioPos.x == -1 || marioPos.y == -1) {
            return false;
        }
		return true;
	}
    else {
        return false;
    }

}
// Function to set the board to the screen state from a file
bool board::setScreen(int screenNumber) {
    std::ostringstream filenameStream;
    filenameStream << "dkong_" << screenNumber << ".screen.txt";
    std::string filename = filenameStream.str();
	std::ifstream file("screens/" + filename);
    if (!file.is_open()) {
        return false;
    }
	for (int i = 0; i < MAX_Y; i++) {
		file.getline(currentBoard[i], MAX_X + 1);
        strncpy_s(currentScreen[i], currentBoard[i], MAX_X + 1);
	}
	fixChar('@');
	fixChar('&');
    return true;
}

void board::fixBoard() {
	for (int i = 0; i < MAX_Y; i++) {
		strncpy_s(currentBoard[i], currentScreen[i], MAX_X + 1);
	}
}

// Function to set the board to the game state
void board::setGame() {
    // Loop through all rows and copy the game board to the current board
    for (int i = 0; i < MAX_Y; i++) {
        memcpy(currentBoard[i], gameBoard[i], MAX_X + 1);  // Copy each row with an additional null terminator
    }
}

// Function to set the board to the guide state
void board::setGuide() {
    // Loop through all rows and copy the guide board to the current board
    for (int i = 0; i < MAX_Y; i++) {
        memcpy(currentBoard[i], guideBoard[i], MAX_X + 1);  // Copy each row with an additional null terminator
    }
}

void board::setChooseScreen() {
	// Loop through all rows and copy the guide board to the current board
	for (int i = 0; i < MAX_Y; i++) {
		memcpy(currentBoard[i], chooseScreenBoard[i], MAX_X + 1);  // Copy each row with an additional null terminator
	}
}

// Function to set the board to the Error screen state
void board::setScreenError() {
	// Loop through all rows and copy the guide board to the current board
	for (int i = 0; i < MAX_Y; i++) {
		memcpy(currentBoard[i], screenErrorBoard[i], MAX_X + 1);  // Copy each row with an additional null terminator
	}
}

// Function to set the board to the win state
void board::setWin() {
    // Loop through all rows and copy the win board to the current board
    for (int i = 0; i < MAX_Y; i++) {
        memcpy(currentBoard[i], winBoard[i], MAX_X + 1);  // Copy each row with an additional null terminator
    }
}

// Function to set the board to the lose state
void board::setLose() {
    // Loop through all rows and copy the lose board to the current board
    for (int i = 0; i < MAX_Y; i++) {
        memcpy(currentBoard[i], loseBoard[i], MAX_X + 1);  // Copy each row with an additional null terminator
    }
}

// Function to change the pixel at a specific position on the current board
void board::changePixel(Pos pos, char ch) {
    // Modify the character at the given position (x, y) in the current board
    currentBoard[pos.y][pos.x] = ch;
}

// Function to print the current board to the console
void board::print() const {
    // Move the cursor to the top-left corner
    gotoxy(0, 0);

    // Loop through all rows (except the last one) and print each line
    for (int i = 0; i < MAX_Y - 1; i++) {
        std::cout << currentBoard[i] << '\n';  // Print each row with a newline after it
    }
    // Print the last row without a newline after it
    std::cout << currentBoard[MAX_Y - 1];
}

void board::fixChar(char c) {
    bool found = false;
    Pos res = { -1,-1 };
    for (int y = 0; y < MAX_Y; y++) {
        for (int x = 0; x < MAX_X; x++) {
            if (currentScreen[y][x] == c) {
                if (!found) {
                    res = { x, y };
                    found = true;
                }
                else {
                    currentScreen[res.y][res.x] = SpecialCharacters::SPACE;
                    currentBoard[res.y][res.x] = SpecialCharacters::SPACE;
                    res = { x, y };
                }

            }
        }
    }
}


Pos board::searchChar(char c) const {
	// Loop through all rows and columns to find the character c
	bool found = false;
    Pos res = { -1,-1 };
	for (int y = 0; y < MAX_Y; y++) {
		for (int x = 0; x < MAX_X; x++) {
			if (currentScreen[y][x] == c){
                res = { x, y };  
			}
		}
	}
    return res;
}
