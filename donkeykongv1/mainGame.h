#pragma once
#include "barrelGroup.h"
#include "menu.h"
#include "mario.h"
#include "board.h"
#include "barrel.h"

// The mainGame class manages the overall game logic and states
class mainGame
{
    int marioLifes = 3;        // Tracks Mario's remaining lives
    board _board;              // Game board object
    mario _mario;              // Mario character object
    barrel barrel;             // Single barrel object
    barrelGroup _BG;           // Group of barrels to manage barrel logic

public:
    // Checks if Mario has no remaining lives
    bool isMarioDead() const{
        return marioLifes == 0;
    }

    // Decrements Mario's life count
    void marioLoseLife() {
        marioLifes--;
    }

    // Prints the remaining lives of Mario
    void printLifes() const;

    // Pauses the game until the user resumes
    void pauseGame() const;

    // Starts the main game loop
    void startGame(int screenNumber);

    // Handles the game-over state
    void gameOver();

    // Handles the game-win state
    void gameWin();
};
