#pragma once
#include <windows.h>

void gotoxy(int x, int y);
void ShowConsoleCursor(bool showFlag);
struct Pos { // Position Struct
	int x, y;
};
struct Direction { // inner private struct
	int x, y;
};
