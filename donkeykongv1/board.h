#pragma once
#include "utils.h"
// The `board` class manages the game's visuals, including different game states and rendering.
class board {
	// Constants defining the board dimensions
	static constexpr int MAX_X = 80;
	static constexpr int MAX_Y = 25;

	// Current board state used for rendering on-screen
	char currentBoard[MAX_Y][MAX_X + 1]; // +1 for null terminator
	const char* gameBoard[MAX_Y] = {
	// 01234567890123456789012345678901234567890123456789012345678901234567890123456789
	  "QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ", // 0
	  "Q                                                                              Q", // 1
	  "Q    Life :                                     $                              Q", // 2
	  "Q                                           =========                          Q", // 3
	  "Q                                               H                              Q", // 4
	  "Q                                               H                              Q", // 5
	  "Q                                               H     &                        Q", // 6
	  "Q                         <<<<<<<<<<<<<<<<<<<<<<<<<<<<<                        Q", // 7
	  "Q                             H                                                Q", // 8
	  "Q                             H                                                Q", // 9
	  "Q                             H                                                Q", // 10
	  "Q                   >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>               Q", // 11
	  "Q                                                    H                         Q", // 12
	  "Q                                                    H                         Q", // 13
	  "Q                                                    H                         Q", // 14
	  "Q             <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<        Q", // 15
	  "Q                      H                                                       Q", // 16
	  "Q                      H                                                       Q", // 17
	  "Q                      H                                                       Q", // 18
	  "Q             >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>       Q", // 19
	  "Q                                                            H                 Q", // 20
	  "Q                                                            H                 Q", // 21
	  "Q                                                            H                 Q", // 22
	  "Q==============================================================================Q", // 23
	  "QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ"  // 24
	};
	const char* winBoard[MAX_Y]= {
   //01234567890123456789012345678901234567890123456789012345678901234567890123456789
	"QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ", // 0
	"Q                                                                              Q", // 1
	"Q                                                                              Q", // 2
	"Q                                                                              Q", // 3
	"Q                                                                              Q", // 4
	"Q                                                                              Q", // 5
	"Q                                                                              Q", // 6
	"Q                               Y O U   W O N !                                Q", // 7
	"Q                                                                              Q", // 9
	"Q                                                                              Q", // 9
	"Q                                                                              Q", // 10
	"Q                                                                              Q", // 11
	"Q                       Press ESC to go back to the menu                       Q", // 12
	"Q                                                                              Q", // 13
	"Q                                                                              Q", // 14
	"Q                                                                              Q", // 15
	"Q                                                                              Q", // 16
	"Q                                                                              Q", // 17
	"Q                                                                              Q", // 18
	"Q                                                                              Q", // 19
	"Q                                                                              Q", // 20
	"Q                                                                              Q", // 21
	"Q                                                                              Q", // 22
	"Q==============================================================================Q", // 23
	"QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ"  // 24
	};
	const char* loseBoard[MAX_Y] = {
		//01234567890123456789012345678901234567890123456789012345678901234567890123456789
		 "QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ", // 0
		 "Q                                                                              Q", // 1
		 "Q                                                                              Q", // 2
		 "Q                                                                              Q", // 3
		 "Q                                                                              Q", // 4
		 "Q                                                                              Q", // 5
		 "Q                                                                              Q", // 6
		 "Q                          ||     GAME   OVER     ||                           Q", // 7
		 "Q                                                                              Q", // 9
		 "Q                                                                              Q", // 9
		 "Q                                                                              Q", // 10
		 "Q                                                                              Q", // 11
		 "Q                       Press ESC to go back to the menu                       Q", // 12
		 "Q                                                                              Q", // 13
		 "Q                                                                              Q", // 14
		 "Q                                                                              Q", // 15
		 "Q                                                                              Q", // 16
		 "Q                                                                              Q", // 17
		 "Q                                                                              Q", // 18
		 "Q                                                                              Q", // 19
		 "Q                                                                              Q", // 20
		 "Q                                                                              Q", // 21
		 "Q                                                                              Q", // 22
		 "Q==============================================================================Q", // 23
		 "QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ"  // 24
	};
	const char* manuBoard[MAX_Y] = {
		// 01234567890123456789012345678901234567890123456789012345678901234567890123456789
		  "QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ", // 0
		  "Q                                                                              Q", // 1
		  "Q                                                                              Q", // 2
		  "Q                              ***   Manu   ***                                Q", // 3
		  "Q                                                                              Q", // 4
		  "Q                                                                              Q", // 5
		  "Q                                                                              Q", // 6
		  "Q                         Press 1 - Start a new game                           Q", // 7
		  "Q                                                                              Q", // 8
		  "Q                                                                              Q", // 9
		  "Q                                                                              Q", // 10
		  "Q                                                                              Q", // 11
		  "Q                                                                              Q", // 12
		  "Q                                                                              Q", // 13
		  "Q                                                                              Q", // 14
		  "Q                                                                              Q", // 15
		  "Q                                                                              Q", // 16
		  "Q                    Press 8 - Present instructions and keys                   Q", // 17
		  "Q                               Press 9 - EXIT                                 Q", // 18
		  "Q                                                                              Q", // 19
		  "Q                                                                              Q", // 20
		  "Q                                                                              Q", // 21
		  "Q                                                                              Q", // 22
		  "Q                                                                              Q", // 23
		  "QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ"  // 24
	};
	const char* guideBoard[MAX_Y] = {
		// 01234567890123456789012345678901234567890123456789012345678901234567890123456789
		  "QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ", // 0
		  "Q                                                                              Q", // 1
		  "Q                           ~~~ INSTRUCTIONS ~~~                               Q", // 2
		  "Q                                                                              Q", // 3
		  "Q                     PRESS ESC TO EXIT THE INSTRUCTIONS                       Q", // 4
		  "Q                         How to Play Donkey Kong:                             Q", // 5
		  "Q                                                                              Q", // 6
		  "Q    - The objective is to navigate your character to the top of the screen,   Q", // 7
		  "Q      avoiding barrels and other obstacles, to rescue the princess.           Q", // 8
		  "Q    - Use the keys below to control your character.                           Q", // 9
		  "Q                                                                              Q", // 10
		  "Q                                CONTROLS:                                     Q", // 11
		  "Q                             A - Move Left                                    Q", // 12
		  "Q                             D - Move Right                                   Q", // 13
		  "Q                             W - Jump / Move Up                               Q", // 14
		  "Q                             X - Move Down                                    Q", // 15
		  "Q                             S - Stay in Place                                Q", // 16
		  "Q                                                                              Q", // 17
		  "Q                                                                              Q", // 18
		  "Q     - Avoid barrels by jumping over them or moving out of their path.        Q", // 19
		  "Q     - Climb ladders to progress to the next level.                           Q", // 20
		  "Q    - Time your moves carefully to avoid falling or getting hit by obstacles. Q", // 21
		  "Q                                                                              Q", // 22
		  "Q                          Good luck and have fun!                             Q", // 23
		  "QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ"  // 24
	};
public:
	// Updates a specific position on the board
	void changePixel(Pos pos, char ch);

	// Sets the current board to the menu state
	void setMenu();

	// Sets the current board to the game state
	void setGame();

	// Sets the current board to the guide state
	void setGuide();

	// Sets the current board to the lose state
	void setLose();

	// Sets the current board to the win state
	void setWin();

	// Prints the current board to the console
	void print() const;

	// Gets a character from the current board
	char getCharFromCurrentBoard(int x, int y) const {
		return currentBoard[y][x];
	}

	// Gets a character from the original game board
	char getCharFromOriginalBoard(int x, int y) const {
		return gameBoard[y][x];
	}
};

