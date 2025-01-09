#pragma once
#include "GhostGroup.h"
#include "barrelGroup.h"

class Enemy : public GhostGroup, public barrelGroup {
public:
    // Constructor
    Enemy()
        : GhostGroup(), barrelGroup() {
        // Initialize enemies on the board
        clearAll(); // Clear ghosts
        resetAll(); // Reset barrels
    }

    // Move all enemies (ghosts + barrels)
    void moveEnemies() {
        moveGhosts(); // Move ghosts
        moveBarrels(); // Move barrels
    }

    // Draw all enemies (ghosts + barrels)
    void drawEnemies() {
        drawGhosts(); // Draw ghosts
        drawBarrels(); // Draw barrels
    }

    // Erase all enemies (ghosts + barrels)
    void eraseEnemies() {
        eraseGhosts(); // Erase ghosts
        eraseBarrels(); // Erase barrels
    }

    // Handle hammer hit for all enemies
    void handleHammerHit(Pos marioPos, int dirX) {
        hammerHitGG(marioPos, dirX); // Check hammer hit on ghosts
        hammerHitBG(marioPos, dirX); // Check hammer hit on barrels
    }
};
