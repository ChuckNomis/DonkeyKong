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
    void Draw(char c) const {
        gotoxy(_pos.x, _pos.y);
        std::cout << c;
    }

public:
    // Constructor: Initializes the enemy with position, direction, board pointer, and character
    Enemy(Direction newDir, Pos newPos, board* Board, char ch)
        : _dir(newDir), _pos(newPos), _pBoard(Board), c(ch) {
    }

    // Draw the enemy on the board
    void draw(bool isSilent) {
        if (!isSilent) {
        Draw(c);
        }
        _pBoard->changePixelInCurrBoard(_pos, c);
        
    }

    // Erase the enemy from the board
    void erase() {
        _pBoard->changePixelInCurrBoard(_pos, SpecialCharacters::SPACE);

        Draw(SpecialCharacters::SPACE);
    }

    // Erase the enemy if it is on a ladder
    void eraseOnLadder(bool isSilent) {
        _pBoard->changePixelInCurrBoard(_pos, SpecialCharacters::LADDER);
        if (!isSilent) {
            Draw(SpecialCharacters::LADDER);
        }
    }

    // Erase the enemy if it is on a hammer
    void eraseOnHammer(bool isSilent) {
        _pBoard->changePixelInCurrBoard(_pos, SpecialCharacters::HAMMER);
        if (!isSilent) {
            Draw(SpecialCharacters::HAMMER);
        }
    }

    // Erase the enemy if it is on Donkey Kong
    void eraseOnKong(bool isSilent) {
        _pBoard->changePixelInCurrBoard(_pos, SpecialCharacters::KONG);
        if (!isSilent) {
            Draw(SpecialCharacters::KONG);
        }
    }

    // Erase the enemy if it is on Pauline
    void eraseOnPauline(bool isSilent) {
        _pBoard->changePixelInCurrBoard(_pos, SpecialCharacters::PAULINE);
        if (!isSilent) {
            Draw(SpecialCharacters::PAULINE);
        }
    }

    // Get the current position of the enemy
    Pos getPos() {
        return _pos;
    }
    Direction getDir() {
        return _dir;
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
    // Flips the diraction of the ghost
    void flipDir() {
        _dir.x *= -1;
    }
    // Get random dir.x
    int getRandomDirx(){
        int x = (rand() % 2 == 0) ? -1 : 1;
        return x;

    }
};
