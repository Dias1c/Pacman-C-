//
//	Menu.h
//
#pragma once

#include <iostream>
#include <time.h>	// clock(), time()
#include <conio.h>  // _kbhit()  _getch()
#include <Windows.h>
#include <vector>

#include "Win10.h"


//======class Menu=======
class Menu { //Меню не будет работать без Windows.h, vector, conio.h, enum COLOR, enum ARROW
	vector <string> Titles; // Меню заголовки

	int ColorTextDef;	// Цвет стандартного текста
	int ColorTextChg;	// Цвет Выбранного текста
	int yRow, xCol;		// Позиция меню
	int Count;			// Колво в меню
	int Select;			// Выбранный заголовок
public:
	Menu();
	Menu(string title, int ColTextDef = _BLUE, int ColTextChg = _GREEN, int xPos = 10, int yPos = 10);
	~Menu();

	//Getters
	virtual int getSelect(); //Возвращяет выбранный индекс 
	virtual string getSelect(int index); //Возвращяет элемент выбранного индекса
	virtual int getSelect(const string& title); //Возвращяет элемент индекса выбранного элемента 
	virtual int getCount(); // Вывод колво элементов в меню

	//Setters
	virtual void setColorTxtDef(int Color = _BLUE);
	virtual void setColorTxtChg(int Color = _GREEN);
	virtual void setPos(int xCol, int yRow);

	//Any Methods
	virtual void addTitle(const string& title); //Добавление Загаловка в меню
	//void delTitle();
	virtual void UpSelect(bool Transition = true); // Перемещения курсора Вверх
	virtual void DownSelect(bool Transition = true); // Перемещения курсора Вниз
	virtual void Show(); // Показ все меню (Для управления курсором используй DownSelect/UpSelect)
};//======End class Menu;=======


//====== Вспомогательные функции для меню ========
// ф-ция ожидания dwMilSeconds милисекунд или нажатия кнопки
//  clock() - возвращает время в милисекундах прошедшее с начала запуска программы
//   возвращаемый тип clock_t соответствует long
void WaitPause(DWORD dwMilSeconds);
void ShowStartTitle(DWORD dwMilSeconds = 2000, string title = "Game Title", int xCol = 3, int yRow = 6, bool Loading = true); // по умолчанию пауза 2 секунды