#pragma once
#include "board.h"
#include "utils.h"
#include "Ghost.h"
#include <iostream>
#include <windows.h>
#include <conio.h>
#include <vector>
#include <cstdlib> // For rand()

class GhostGroup {

public:
    std::vector<Ghost> _ghostGroup; // Vector to hold the ghosts
    // Clears all ghosts from the group
    void clearAll() {
        _ghostGroup.clear();
    }

    // Places a ghost on the board at the specified position
    void setGhostOnBoard(board& board, Pos newPos);

    // Returns a random horizontal direction (-1 or 1)
    Direction getEvenRandomDir() {
        int x = (rand() % 2 == 0) ? -1 : 1;
        return { x, 0 };
    }

    // Moves all ghosts in the group
    void moveGhosts();

    // Draws all ghosts in the group on the board
    void drawGhosts();

    // Erases all ghosts from the board
    void eraseGhosts();

    // Checks if the hammer hits any ghosts, updating the score if so
    bool hammerHitGG(Pos marioPos, int dirX, int& gameScore);
};
