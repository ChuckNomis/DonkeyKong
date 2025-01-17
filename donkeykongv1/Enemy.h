#pragma once
#include "board.h"
#include "utils.h"
#include <iostream>
#include <windows.h>
#include <conio.h>

class Enemy {
protected:
    Pos _pos;                 // Position of the enemy
    Direction _dir;           // Direction of movement
    board* _pBoard;           // Pointer to the game board
    char c;                   // Character representing the enemy

    // Draw the enemy at its current position
    void draw(char c) const {
        gotoxy(_pos.x, _pos.y);
        std::cout << c;
    }

public:
    // Constructor: Initializes the enemy with position, direction, board pointer, and character
    Enemy(Direction newDir, Pos newPos, board* Board, char ch)
        : _dir(newDir), _pos(newPos), _pBoard(Board), c(ch) {
    }

    // Draw the enemy on the board
    void draw() {
        _pBoard->changePixelInCurrBoard(_pos, c);
        draw(c);
    }

    // Erase the enemy from the board
    void erase() {
        _pBoard->changePixelInCurrBoard(_pos, SpecialCharacters::SPACE);
        draw(SpecialCharacters::SPACE);
    }

    // Erase the enemy if it is on a ladder
    void eraseOnLadder() {
        _pBoard->changePixelInCurrBoard(_pos, SpecialCharacters::LADDER);
        draw(SpecialCharacters::LADDER);
    }

    // Erase the enemy if it is on a hammer
    void eraseOnHammer() {
        _pBoard->changePixelInCurrBoard(_pos, SpecialCharacters::HAMMER);
        draw(SpecialCharacters::HAMMER);
    }

    // Erase the enemy if it is on Donkey Kong
    void eraseOnKong() {
        _pBoard->changePixelInCurrBoard(_pos, SpecialCharacters::KONG);
        draw(SpecialCharacters::KONG);
    }

    // Erase the enemy if it is on Pauline
    void eraseOnPauline() {
        _pBoard->changePixelInCurrBoard(_pos, SpecialCharacters::PAULINE);
        draw(SpecialCharacters::PAULINE);
    }

    // Get the current position of the enemy
    Pos getPos() {
        return _pos;
    }

    // Check if the enemy is on a ladder
    bool checkLadder() {
        return _pBoard->getCharFromOriginalScreen(_pos.x, _pos.y) == SpecialCharacters::LADDER;
    }

    // Check if the enemy is on a hammer
    bool checkHammer() {
        return _pBoard->getCharFromOriginalScreen(_pos.x, _pos.y) == SpecialCharacters::HAMMER;
    }

    // Check if the enemy is on Pauline
    bool checkPauline() {
        return _pBoard->getCharFromOriginalScreen(_pos.x, _pos.y) == SpecialCharacters::PAULINE;
    }

    // Check if the enemy is on Donkey Kong
    bool checkDkong() {
        return _pBoard->getCharFromOriginalScreen(_pos.x, _pos.y) == SpecialCharacters::KONG;
    }
};
