//
//Win10.cpp
//

#pragma once

#include "Win10.h"

void SetPos(int x, int y)
{
	COORD cd;
	cd.X = x;
	cd.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cd);
}
void SetColor(WORD wAttributes)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), wAttributes);
}
void SetColor(int colBkgr, int colSym) {
	SetColor(colBkgr * 16 + colSym);
}


//typedef vector<string> TypePole;