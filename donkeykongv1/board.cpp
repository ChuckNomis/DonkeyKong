#include <cstring>
#include <iostream>
#include "board.h"
#include "utils.h"
#include <fstream>
#include <string>
#include <sstream>


//Get the locations of all the ghosts on the screen
std::vector<Pos> board::getGhostsLocations() {
	std::vector<Pos> ghostPos;
	for (int i = 0; i < MAX_Y; i++) {
		for (int j = 0; j < MAX_X; j++) {
			if (currentScreen[i][j] == SpecialCharacters::GHOST) {
				ghostPos.push_back({ j,i });
			}
		}
	}
	return ghostPos;
}

// Function to choose a screen from a list of files
int board::chooseScreen(std::vector<std::string> const FileNames, const int sumOfFiles) {
    int screenNumber = 1;
	int result = 0;
	int line = 0, row = 0;
    gotoxy(3 + row, 6 + line);
    for (std::string name : FileNames) {
        std::cout << screenNumber << ". " << name << std::endl;
        screenNumber++;
		if (line == 8) {
			line = 0;
			row += 25;
		}
		else {
			line += 1;
		}
        gotoxy(3 + row, 6 + line);
    }

	gotoxy(34,19);
	std::cout << "Screen : ";
	std::cin >> result;

	if (result > 0 && result <= sumOfFiles) {
		return result;
	}
	else {
		return 0;
	}
}

void board::setScoreBoard() {
    for (int i = 0; i < MAX_Y; i++) {
        memcpy(currentBoard[i], scoreBoard[i], MAX_X + 1);
    }
}

// Function to set the board to the menu state
void board::setMenu() {
    for (int i = 0; i < MAX_Y; i++) {
        memcpy(currentBoard[i], manuBoard[i], MAX_X + 1); 
    }
}

// Function to check if a screen file is valid (contains Mario and Donkey Kong)
bool board::isScreenOk(int screenNumber) {
	std::ostringstream filenameStream;
	filenameStream << "dkong_" << screenNumber << ".screen.txt";
	std::string filename = filenameStream.str();
    std::ifstream file("screens/" + filename);
    if (file.is_open()) {
        Pos donkeyKongPos = searchChar(SpecialCharacters::KONG);
        if (donkeyKongPos.x == -1 || donkeyKongPos.y == -1) {
            return false;
        }
        Pos marioPos = searchChar(SpecialCharacters::MARIO);
        if (marioPos.x == -1 || marioPos.y == -1) {
            return false;
        }
        Pos paulinePos = searchChar(SpecialCharacters::PAULINE);
        if (paulinePos.x == -1 || paulinePos.y == -1) {
            return false;
        }
        Pos legendPos = searchChar(SpecialCharacters::LEGEND);
        if (legendPos.x == -1 || legendPos.y == -1) {
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
	fixChar(SpecialCharacters::MARIO);
	fixChar(SpecialCharacters::KONG);
    fixGhosts();
    return true;
}

// Fix Ghosts on the screen (delete any flying ghosts)
void board::fixGhosts() {
    for (int y = 0; y < MAX_Y; y++) {
        for (int x = 0; x < MAX_X; x++) {
            if (currentScreen[y][x] == SpecialCharacters::GHOST &&
                currentScreen[y+1][x] == SpecialCharacters::SPACE) {
                currentScreen[y][x] = SpecialCharacters::SPACE;
                currentBoard[y][x] = SpecialCharacters::SPACE;
            }

        }
    }
    
}

// Function to set the board to the screen state from a file
void board::fixBoard() {
	for (int i = 0; i < MAX_Y; i++) {
		strncpy_s(currentBoard[i], currentScreen[i], MAX_X + 1);
	}
}

// Function to set the board to the no files error state
void board::setNoFilesError() {
	for (int i = 0; i < MAX_Y; i++) {
		memcpy(currentBoard[i], noFilesErrorBoard[i], MAX_X + 1);
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

// Function to set the board to the choose screen state
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


// Function to print the current board to the console
void board::print() const {
    // Move the cursor to the top-left corner
    system("cls");

    gotoxy(0, 0);

    // Loop through all rows (except the last one) and print each line
    for (int i = 0; i < MAX_Y - 1; i++) {
        std::cout << currentBoard[i] << '\n';  // Print each row with a newline after it
    }
    // Print the last row without a newline after it
    std::cout << currentBoard[MAX_Y - 1];
}

// Function to search for a specific character on the board delete if there are duplicates
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

// Function to search for a specific character on the board and return its position (if found)
Pos board::searchChar(char c) const {
	// Loop through all rows and columns to find the character c
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
