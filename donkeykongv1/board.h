#pragma once
#include "utils.h"
class board {
	static constexpr char WALL_CHAR = 'W';
	static constexpr char FLOOR_CHAR = '=';
	static constexpr char LFLOOR_CHAR = '<';
	static constexpr char RFLOOR_CHAR = '>';
	static constexpr char LADDER_CHAR = 'H';
	static constexpr int MAX_X = 80;
	static constexpr int MAX_Y = 25;
	char currentBoard[MAX_Y][MAX_X + 1]; // +1 for null terminator
	const char* gameBoard[MAX_Y] = {
	// 01234567890123456789012345678901234567890123456789012345678901234567890123456789
	  "WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW", // 0
	  "W                                                                              W", // 1
	  "W                                               $                              W", // 2
	  "W                                           =========                          W", // 3
	  "W                                               H                              W", // 4
	  "W                                               H                              W", // 5
	  "W                                               H     &                        W", // 6
	  "W                         <<<<<<<<<<<<<<<<<<<<<<<<<<<<<                        W", // 7
	  "W                             H                                                W", // 8
	  "W                             H                                                W", // 9
	  "W                             H                                                W", // 10
	  "W                   >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>                    W", // 11
	  "W                                                    H                         W", // 12
	  "W                                                    H                         W", // 13
	  "W                                                    H                         W", // 14
	  "W             <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<             W", // 15
	  "W                      H                                                       W", // 16
	  "W                      H                                                       W", // 17
	  "W                      H                                                       W", // 18
	  "W          >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>      W", // 19
	  "W                                                            H                 W", // 20
	  "W                                                            H                 W", // 21
	  "W                                                            H                 W", // 22
	  "W==============================================================================W", // 23
	  "WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW"  // 24
	};
	const char* manuBoard[MAX_Y] = {
		// 01234567890123456789012345678901234567890123456789012345678901234567890123456789
		  "WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW", // 0
		  "W                                                                              W", // 1
		  "W                                                                              W", // 2
		  "W                              ***   Manu   ***                                W", // 3
		  "W                                                                              W", // 4
		  "W                                                                              W", // 5
		  "W                                                                              W", // 6
		  "W                         Press 1 - Start a new game                           W", // 7
		  "W                                                                              W", // 8
		  "W                                                                              W", // 9
		  "W                                                                              W", // 10
		  "W                                                                              W", // 11
		  "W                                                                              W", // 12
		  "W                                                                              W", // 13
		  "W                                                                              W", // 14
		  "W                                                                              W", // 15
		  "W                                                                              W", // 16
		  "W                    Press 8 - Present instructions and keys                   W", // 17
		  "W                               Press 9 - EXIT                                 W", // 18
		  "W                                                                              W", // 19
		  "W                                                                              W", // 20
		  "W                                                                              W", // 21
		  "W                                                                              W", // 22
		  "W                                                                              W", // 23
		  "WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW"  // 24
	};
	const char* guideBoard[MAX_Y] = {
		// 01234567890123456789012345678901234567890123456789012345678901234567890123456789
		  "WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW", // 0
		  "W                                                                              W", // 1
		  "W                           ~~~ INSTRUCTIONS ~~~                               W", // 2
		  "W                                                                              W", // 3
		  "W                          How to Play Donkey Kong:                            W", // 4
		  "W                                                                              W", // 5
		  "W                                                                              W", // 6
		  "W    - The objective is to navigate your character to the top of the screen,   W", // 7
		  "W      avoiding barrels and other obstacles, to rescue the princess.           W", // 8
		  "W    - Use the keys below to control your character.                           W", // 9
		  "W                                                                              W", // 10
		  "W                                CONTROLS:                                     W", // 11
		  "W                             A - Move Left                                    W", // 12
		  "W                             D - Move Right                                   W", // 13
		  "W                             W - Jump / Move Up                               W", // 14
		  "W                             X - Move Down                                    W", // 15
		  "W                             S - Stay in Place                                W", // 16
		  "W                                                                              W", // 17
		  "W                                                                              W", // 18
		  "W     - Avoid barrels by jumping over them or moving out of their path.        W", // 19
		  "W     - Climb ladders to progress to the next level.                           W", // 20
		  "W    - Time your moves carefully to avoid falling or getting hit by obstacles. W", // 21
		  "W                                                                              W", // 22
		  "W                          Good luck and have fun!                             W", // 23
		  "WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW"  // 24
	};
public:
	void changePixel(Pos pos,char ch);
	void setMenu();
	void setGame();
	void setGuide();
	void print() const;
	char getChar(int x, int y) const {
		return currentBoard[y][x];
	}
};

