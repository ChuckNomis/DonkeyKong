#pragma once
#include <windows.h>

// Enumeration for special characters used in the game
enum SpecialCharacters {
	LADDER = 'H', // Ladder character
	FLOOR = '=', // Floor top character
	FLOOR_RIGHT = '>', // Floor right character
	FLOOR_LEFT = '<', // Floor left character
	BARREL = 'O', // Barrel character
	MARIO = '@', // Mario character
	KONG = '&', // Kong character
	PAULINE = '$', // Pauline character
	SPACE = ' ', // Space character
	BORDER = 'Q', // Border character
	EXPLOSION = 'X', // Explosion character
	MARIO_ON_LADDER = '%', // Mario on ladder character
	GHOST = 'x', // Ghost character
	HAMMER = 'p', // Hammer character 
	LEGEND = 'L'
};
// Enumeration for key codes
enum KeyCode {
	KEY_HAMMER = 'p',
	KEY_ENTER = 13,
	KEY_UP = 'w',
	KEY_DOWN = 'x',
	KEY_LEFT = 'a',
	KEY_RIGHT = 'd',
	KEY_STAY = 's',
	KEY_ESC = 27,
};

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
