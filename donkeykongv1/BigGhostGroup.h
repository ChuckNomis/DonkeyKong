#pragma once
#include "board.h"
#include "utils.h"
#include "BigGhost.h"
#include <iostream>
#include <windows.h>
#include <conio.h>
#include <vector>
#include <cstdlib> // For rand()
class BigGhostGroup
{
	
public:
    std::vector<BigGhost> _BigGhostGroup; // Vector to hold the ghosts
    // Clears all ghosts from the group
    void clearAll() {
        _BigGhostGroup.clear();
    }
    // Places a big ghost on the board at the specified position
    void setBigGhostOnBoard(board& board, Pos newPos);
    // Returns a random horizontal direction (-1 or 1)
    Direction getEvenRandomDir() {
        int x = (rand() % 2 == 0) ? -1 : 1;
        return { x, 0 };
    }
    // Moves all ghosts in the group
    void moveBigGhosts();

    // Draws all ghosts in the group on the board
    void drawBigGhosts(bool isSilent);

    // Erases all ghosts from the board
    void eraseBigGhosts(bool isSilent);

    // Checks if the hammer hits any big ghosts, updating the score if so
    bool hammerHitBGG(Pos marioPos, int dirX, int& gameScore,bool isSilent);
};

