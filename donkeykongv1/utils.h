#pragma once
#include <windows.h>

// Moves the cursor to the specified (x, y) position on the console screen
void gotoxy(int x, int y);

// Toggles the visibility of the console cursor
void ShowConsoleCursor(bool showFlag);

// Structure to represent a position (x, y) on the console or board
struct Pos {
	int x, y; // x: horizontal position, y: vertical position
};

// Structure to represent direction for movement (x, y)
struct Direction {
	int x, y; // x: horizontal direction (-1, 0, 1), y: vertical direction (-1, 0, 1)
};
