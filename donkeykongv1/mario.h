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
    static constexpr char keys[] = { KeyCode::KEY_LEFT, KeyCode::KEY_RIGHT, KeyCode::KEY_STAY };
    static constexpr size_t numKeys = sizeof(keys) / sizeof(keys[0]);

    // Directions corresponding to the keys array
    static constexpr Direction directions[] = { {-1, 0}, {1, 0}, {0, 0} };

    // Mario's position and direction
    Pos marioPos;
    Direction dir;  

    // Character used to represent Mario on the board
    char ch;

    //Indicates if mario has the hammer 
    bool hammerTime = false;

    // Pointer to the game board
    board* pBoard;

    // Draw Mario or other characters on the board at his current position
    void draw(char c) const {
        gotoxy(marioPos.x, marioPos.y); 
        std::cout << c; 
    }

public:

    // Constructor
    mario(Pos marioPos = { 0, 0 }, Direction dir = { 0, 0 }, char ch = SpecialCharacters::MARIO, board* pBoard = nullptr)
        : marioPos(marioPos), dir(dir), ch(ch), pBoard(pBoard) {
    }

    // Set Mario's direction
    void setDir(int _x, int _y) {
        dir.x = _x;
        dir.y = _y;
    }

    // Check if mario picked up the hammer
    bool isHammerTime() {
        return hammerTime;
    }
    // Check if mario is on Hammer
    void checkHammer() {
        if (pBoard->getCharFromCurrentBoard(marioPos.x, marioPos.y) == SpecialCharacters::HAMMER) {
            hammerTime = true;
            pBoard->changePixelInScreen(marioPos, SpecialCharacters::SPACE);
            
        }
    }

    Pos getMarioPos() {
        return marioPos;
    }


    // Set Mario's vertical direction
    void setDirY(int y) {
        dir.y = y;
    }

    int getDirX(){
        return dir.x;
    }

    // Check if Mario is currently falling
    bool isMarioFalling() const;

    // Draw Mario at his current position on the board
    void draw() const {
        pBoard->changePixelInCurrBoard(marioPos, SpecialCharacters::MARIO);
        draw(ch);
    }

    // Draw Mario while on a ladder
    void drawOnLadder() const {
        pBoard->changePixelInCurrBoard(marioPos, SpecialCharacters::LADDER);
        draw(SpecialCharacters::MARIO_ON_LADDER);
    }

    // Erase Mario from his current position
    void erase() {
        pBoard->changePixelInCurrBoard(marioPos, SpecialCharacters::SPACE);
        draw(SpecialCharacters::SPACE);
    }

    // Erase Mario from a ladder position
    void eraseOnLadder() {
        pBoard->changePixelInCurrBoard(marioPos, SpecialCharacters::LADDER);
        draw(SpecialCharacters::LADDER);
    }

    // Handle Mario moving up (jumping or climbing a ladder)
    void up(int& jumps, bool& ladder);

    // Handle Mario moving down (falling or descending a ladder)
    void down(bool& downLadder, bool& ladder);

    // Check if Mario is on a ladder
    bool checkLadder() const;


    // Handle input key presses and adjust Mario's direction
    void keyPressed(char key);

    // Move Mario based on his current direction
    void move();

    // Set Mario's initial position on the board
    void setMarioOnBoard(board& board,Pos newMarioPos) {
        pBoard = &board;  
        marioPos = newMarioPos;
        hammerTime = false;
    }

    // Check if Mario is on the last rung of a ladder
    void isMarioOnLastLadder(bool& downLadder, bool& ladder);

    // Check if Mario is on the first rung of a ladder
    void isMarioOnFirstLadder(bool& downLadder, bool& ladder);

    // Check if Mario is hit by a barrel
    bool isMarioHitBarrel() const;

    // Check if Mario is hit by a ghost
    bool isMarioHitGhost() const;

    // Check if Mario has reached the winning condition
    bool isMarioWin() const;
};
