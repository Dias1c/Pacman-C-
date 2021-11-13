//
//Win10.h
//

#pragma once

#include <iostream>
#include <Windows.h>
#include <fstream>	
#include <time.h>	// clock(), time()
#include <conio.h> // _kbhit()  _getch()
#include <vector>
#include <string>

#pragma warning(disable:4996)

using namespace std;

enum ARROW //Код Кнопок
{
	LEFT = 75,
	RIGHT = 77,
	UP = 72,
	DOWN = 80,
	ESC = 27,
	SPACE = 32,
	ENTER = 13
};

enum Direct {	 /// Перечисления для направлений
	Up = 0,		// = 0 направление Вверх
	Right = 1,  // = 1 направление Вправо
	Down = 2,	// = 2 направление Вниз
	Left = 3,	// = 3 направление Влево
	CountDirections = 4
};

enum COLOR {
	_BLACK,
	_BLUE,
	_GREEN,
	_AQUA,
	_RED,
	_PURPLE,
	_YELLOW,
	_WHITE,
	_GRAY,
	_LIGHT_BLUE,
	_LIGHT_GREEN,
	_LIGHT_AQUA,
	_LIGHT_RED,
	_LIGHT_PURPLE,
	_LIGHT_YELLOW,
	_BRIGHT_WHITE,
};

void SetPos(int x, int y);
void SetColor(WORD wAttributes);
void SetColor(int colBkgr, int colSym);

typedef vector<string> TypePole;
//typedef char TypePole;