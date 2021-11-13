//
// Menu.cpp
//

#include "Win10.h"
#include "Menu.h"

//======class Menu=======
Menu::Menu() :ColorTextDef(_BLUE), ColorTextChg(_GREEN), yRow(0), xCol(0), Count(), Select() {}
Menu::Menu(string title, int ColTextDef, int ColTextChg, int xPos, int yPos)
	: ColorTextDef(ColTextDef), ColorTextChg(ColTextChg), yRow(yPos), xCol(xPos), Count(), Select() {
	addTitle(title);
}
Menu::~Menu() {}

//Getters
int Menu::getSelect() { return Select; } //���������� ��������� ������ 
string Menu::getSelect(int index) { return Titles[index]; } //���������� ������� ���������� �������
int Menu::getSelect(const string& title) //���������� ������� ������� ���������� �������� 
{
	for (int i = 0; i < Count; i++) {
		if (title == Titles[i]) return i;
	}
	return -1;
}
int Menu::getCount() { return Count; }	// ����� ����� ��������� � ����

//Setters
void Menu::setColorTxtDef(int Color) { ColorTextDef = Color; }
void Menu::setColorTxtChg(int Color) { ColorTextChg = Color; }
void Menu::setPos(int xCol, int yRow) { this->yRow = yRow; this->xCol = xCol; }

//Any Methods
void Menu::addTitle(const string& title) //���������� ��������� � ����
{
	Titles.push_back(title);
	Count++;
}
//void delTitle();
void Menu::UpSelect(bool Transition) // ����������� ������� �����
{
	Select--;
	if (Select == -1) {
		Select = Count - 1;
	}
	else if (Select == -1 && Transition == false) {
		Select++;
	}
}
void Menu::DownSelect(bool Transition) // ����������� ������� ����
{
	Select++;
	if (Select == Count) {
		Select = 0;
	}
	else if (Select == Count && Transition == false) {
		Select--;
	}
}
void Menu::Show() // ����� ��� ���� (��� ���������� �������� ��������� DownSelect/UpSelect)
{
	for (int i = 0; i < Count; i++) {
		if (Select == i) {
			SetPos(xCol, yRow + i);
			SetColor(ColorTextChg);
			cout << Titles[i];
		}
		else {
			SetPos(xCol, yRow + i);
			SetColor(ColorTextDef);
			cout << Titles[i];
		}
	}
	SetColor(_WHITE);
}
//======End class Menu;=======


//====== ��������������� ������� ��� ���� ========
void WaitPause(DWORD dwMilSeconds)
{
	clock_t startTimer = clock(); // ������ � ������������
	clock_t endTimer = startTimer + dwMilSeconds; // ����� � ������������
	while (endTimer > clock()) { // ���� �� ����� �����
		if (_kbhit()) { // ������ �� ������
			while (_kbhit()) _getch(); // ������� ����� ����������
			return; // ��������� ������ �-���
		}
	}
}
void ShowStartTitle(DWORD dwMilSeconds, string title, int xCol, int yRow, bool Loading) // �� ��������� ����� 2 �������
{
	system("cls");  // ������� �����
	SetPos(xCol, yRow);   // ������������� ������� ������ �� �����
	SetColor(COLOR::_YELLOW, COLOR::_BLACK);  // ������������� ���� ������
	cout << title << endl;

	//Loading (�� ����� �������� ������ �� ����������, ������ �������� ���������� ������)
	if (Loading) {
		if (title.size()) { title = "Title.size() == 0"; }
		SetColor(COLOR::_GREEN);
		SetPos(xCol - 1, yRow + 2);
		cout << '[';
		for (int i = 0; i < title.size(); i++) {
			cout << " ";
		}
		cout << " ]";

		SetPos(xCol, yRow + 4);
		cout << "To display the shapes correctly in the console,";
		SetPos(xCol, yRow + 5);
		cout << "put \"Dot font, 12x16\".";

		for (int i = 1; i < title.size() + 1; i++) {
			Sleep(dwMilSeconds / title.size());
			SetPos(xCol - 1 + i, yRow + 2);
			SetColor(i % 16);
			cout << char(rand() % 31 + 1) << ">";
		}
		WaitPause(dwMilSeconds / title.size()); // ��������
	}
	else {
		WaitPause(dwMilSeconds); // ��������
	}
	SetColor(COLOR::_BLACK, COLOR::_WHITE); // ��������������� ���� ������� �� ���������
	system("cls");	// ������� ������
}