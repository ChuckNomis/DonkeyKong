#pragma once
#include "menu.h"
#include "mario.h"
#include "board.h"
#include "Enemy.h"


// The mainGame class manages the overall game logic and states
class mainGame
{
    int marioLives = 3;        // Tracks Mario's remaining lives
    board _board;              // Game board object
    mario _mario;              // Mario character object
    Enemy _enemy;              // Enemy Object (consists ghosts and barrel)

public:
    // Checks if Mario has no remaining lives
    bool isMarioDead() const{
        return marioLives == 0;
    }

    // Decrements Mario's life count
    void marioLoseLife() {
        marioLives--;
    }

    // Prints the remaining lives of Mario
    void printLives() const;

    // Pauses the game until the user resumes
    void pauseGame() const;

    // Starts the main game loop
    void startGame(int screenNumber,int numOfFiles);

    // Handles the game-over state
    void gameOver();

    // Handles the game-win state
    void gameWin();

	// Handles the error screen state
	void errorScreenNotGood(int screenNumber);

	bool setALL();

    void itsHammerTime();
};
