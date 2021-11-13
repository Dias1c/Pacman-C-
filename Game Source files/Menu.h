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
class Menu { //���� �� ����� �������� ��� Windows.h, vector, conio.h, enum COLOR, enum ARROW
	vector <string> Titles; // ���� ���������

	int ColorTextDef;	// ���� ������������ ������
	int ColorTextChg;	// ���� ���������� ������
	int yRow, xCol;		// ������� ����
	int Count;			// ����� � ����
	int Select;			// ��������� ���������
public:
	Menu();
	Menu(string title, int ColTextDef = _BLUE, int ColTextChg = _GREEN, int xPos = 10, int yPos = 10);
	~Menu();

	//Getters
	virtual int getSelect(); //���������� ��������� ������ 
	virtual string getSelect(int index); //���������� ������� ���������� �������
	virtual int getSelect(const string& title); //���������� ������� ������� ���������� �������� 
	virtual int getCount(); // ����� ����� ��������� � ����

	//Setters
	virtual void setColorTxtDef(int Color = _BLUE);
	virtual void setColorTxtChg(int Color = _GREEN);
	virtual void setPos(int xCol, int yRow);

	//Any Methods
	virtual void addTitle(const string& title); //���������� ��������� � ����
	//void delTitle();
	virtual void UpSelect(bool Transition = true); // ����������� ������� �����
	virtual void DownSelect(bool Transition = true); // ����������� ������� ����
	virtual void Show(); // ����� ��� ���� (��� ���������� �������� ��������� DownSelect/UpSelect)
};//======End class Menu;=======


//====== ��������������� ������� ��� ���� ========
// �-��� �������� dwMilSeconds ���������� ��� ������� ������
//  clock() - ���������� ����� � ������������ ��������� � ������ ������� ���������
//   ������������ ��� clock_t ������������� long
void WaitPause(DWORD dwMilSeconds);
void ShowStartTitle(DWORD dwMilSeconds = 2000, string title = "Game Title", int xCol = 3, int yRow = 6, bool Loading = true); // �� ��������� ����� 2 �������