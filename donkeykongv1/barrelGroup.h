#pragma once
#include "board.h"
#include "barrel.h"
#include <iostream>
#include <windows.h>
#include <conio.h>

// The barrelGroup class manages a collection of barrels and their behavior
class barrelGroup
{
	Pos _barrelSpawnPos; // Position of the barrel
    barrel _barrelGroup[10]; // Array to hold up to 10 barrels

public:
    // Associates the barrels with the game board
    void setBarrelsBoard(board& board,Pos newPos);

    // Spawns a new barrel at the specified index
    void spawnBarrel(int i);

    // Checks if any barrels are currently falling
    bool barrelsFalling();

    // Erases all barrels from the board
    void eraseBarrels();

    // Moves all barrels according to their current logic
    void moveBarrels();

    // Draws all barrels on the board
    void drawBarrels();

    // Resets all barrels to their initial state
    void resetAll();

    bool hammerHitBG(Pos marioPos,int dirX, int& gameScore);
};
