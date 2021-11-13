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
int Menu::getSelect() { return Select; } //Возвращяет выбранный индекс 
string Menu::getSelect(int index) { return Titles[index]; } //Возвращяет элемент выбранного индекса
int Menu::getSelect(const string& title) //Возвращяет элемент индекса выбранного элемента 
{
	for (int i = 0; i < Count; i++) {
		if (title == Titles[i]) return i;
	}
	return -1;
}
int Menu::getCount() { return Count; }	// Вывод колво элементов в меню

//Setters
void Menu::setColorTxtDef(int Color) { ColorTextDef = Color; }
void Menu::setColorTxtChg(int Color) { ColorTextChg = Color; }
void Menu::setPos(int xCol, int yRow) { this->yRow = yRow; this->xCol = xCol; }

//Any Methods
void Menu::addTitle(const string& title) //Добавление Загаловка в меню
{
	Titles.push_back(title);
	Count++;
}
//void delTitle();
void Menu::UpSelect(bool Transition) // Перемещения курсора Вверх
{
	Select--;
	if (Select == -1) {
		Select = Count - 1;
	}
	else if (Select == -1 && Transition == false) {
		Select++;
	}
}
void Menu::DownSelect(bool Transition) // Перемещения курсора Вниз
{
	Select++;
	if (Select == Count) {
		Select = 0;
	}
	else if (Select == Count && Transition == false) {
		Select--;
	}
}
void Menu::Show() // Показ все меню (Для управления курсором используй DownSelect/UpSelect)
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


//====== Вспомогательные функции для меню ========
void WaitPause(DWORD dwMilSeconds)
{
	clock_t startTimer = clock(); // начало в милисекундах
	clock_t endTimer = startTimer + dwMilSeconds; // конец в милисекундах
	while (endTimer > clock()) { // пока не вышло время
		if (_kbhit()) { // нажали на кнопку
			while (_kbhit()) _getch(); // очищаем буфер клавиатуры
			return; // завершаем работу ф-ции
		}
	}
}
void ShowStartTitle(DWORD dwMilSeconds, string title, int xCol, int yRow, bool Loading) // по умолчанию пауза 2 секунды
{
	system("cls");  // очищаем экран
	SetPos(xCol, yRow);   // устанавливаем позицию вывода на экран
	SetColor(COLOR::_YELLOW, COLOR::_BLACK);  // устанавливаем цвет вывода
	cout << title << endl;

	//Loading (Во время загрузки кнопки не нажимаются, тоесть загрузку пропустить нельзя)
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
		WaitPause(dwMilSeconds / title.size()); // ожидание
	}
	else {
		WaitPause(dwMilSeconds); // ожидание
	}
	SetColor(COLOR::_BLACK, COLOR::_WHITE); // восстанавливаем цвет консоли по умолчанию
	system("cls");	// Очистка Экрана
}