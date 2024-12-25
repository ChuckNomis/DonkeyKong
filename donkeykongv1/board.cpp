#include <cstring>
#include <iostream>
#include "board.h"
#include "utils.h"

// Function to set the board to the menu state
void board::setMenu() {
    // Loop through all rows and copy the menu board to the current board
    for (int i = 0; i < MAX_Y; i++) {
        memcpy(currentBoard[i], manuBoard[i], MAX_X + 1);  // Copy each row with an additional null terminator
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
