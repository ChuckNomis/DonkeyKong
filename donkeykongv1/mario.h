#pragma once
#include <iostream>
#include "utils.h"
#include <cstring>
#include "board.h"

// Class representing Mario and his interactions with the board
class mario
{
    // Constants for Mario's behavior

    // Key bindings for Mario's movement ('a' for left, 'd' for right, 's' for stop)
    static constexpr char keys[] = { 'a', 'd', 's' };
    static constexpr size_t numKeys = sizeof(keys) / sizeof(keys[0]);

    // Directions corresponding to the keys array
    static constexpr Direction directions[] = { {-1, 0}, {1, 0}, {0, 0} };

    // Mario's position and direction
    Pos marioPos; // Initial position of Mario
    Direction dir;  // Starting direction: dir.x, dir.y

    // Character used to represent Mario on the board
    char ch;

    // Pointer to the game board
    board* pBoard;

    // Draw Mario or other characters on the board at his current position
    void draw(char c) const {
        gotoxy(marioPos.x, marioPos.y); 
        std::cout << c; 
    }

public:
    //Constructor
    mario(Pos marioPos = { 30, 22 }, Direction dir = { 0, 0 }, char ch = '@', board* pBoard = nullptr)
        : marioPos(marioPos), dir(dir), ch(ch), pBoard(pBoard) {
    }
    // Set Mario's direction
    void setDir(int _x, int _y) {
        dir.x = _x;
        dir.y = _y;
    }

    // Set Mario's vertical direction
    void setDirY(int y) {
        dir.y = y;
    }

    // Check if Mario is currently falling
    bool isMarioFalling();

    // Draw Mario at his current position on the board
    void draw() const {
        pBoard->changePixel(marioPos, '@'); 
        draw(ch);
    }

    // Draw Mario while on a ladder
    void drawOnLadder() const {
        pBoard->changePixel(marioPos, 'H');
        draw('%'); 
    }

    // Erase Mario from his current position
    void erase() {
        pBoard->changePixel(marioPos, ' '); 
        draw(' '); 
    }

    // Erase Mario from a ladder position
    void eraseOnLadder() {
        pBoard->changePixel(marioPos, 'H'); 
        draw('H'); 
    }

    // Handle Mario moving up (jumping or climbing a ladder)
    void up(int& jumps, bool& ladder);

    // Handle Mario moving down (falling or descending a ladder)
    void down(bool& downLadder, bool& ladder);

    // Check if Mario is on a ladder
    bool checkLadder();

    // Handle input key presses and adjust Mario's direction
    void keyPressed(char key);

    // Move Mario based on his current direction
    void move();

    // Set Mario's initial position on the board
    void setMarioOnBoard(board& board) {
        pBoard = &board;  
        marioPos = { 30, 22 };
    }

    // Check if Mario is on the last rung of a ladder
    void isMarioOnLastLadder(bool& downLadder, bool& ladder);

    // Check if Mario is on the first rung of a ladder
    void isMarioOnFirstLadder(bool& downLadder, bool& ladder);

    // Check if Mario is hit by a barrel
    bool isMarioHitBarrel();

    // Check if Mario has reached the winning condition
    bool isMarioWin();
};
