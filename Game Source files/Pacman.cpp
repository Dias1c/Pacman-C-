//
// Pacman.cpp
//

#include <iostream>
#include <string>
#include <vector>
#include <conio.h>
#include "Win10.h"
#include "Pacman.h"
using namespace std;


Object::Object() : Image('E'), x(), y(), OldX(), OldY() {}
Object::Object(int x, int y, char Image) : OldX(x), OldY(y), x(x), y(y), Image(Image) {}

int Object::getX() const { return x; }
int Object::getY() const { return y; }
int Object::getOldX() const { return OldX; }
int Object::getOldY() const { return OldY; }

char Object::getImage() const { return Image; }

void Object::setX(int x) { this->x = x; }
void Object::setY(int y) { this->y = y; }
void Object::setOldX(int x) { this->OldX = x; }
void Object::setOldY(int y) { this->OldY = y; }	

void Object::setImage(char Image) { this->Image = Image; }

//void Object::Draw() {
//	SetPos(0, 0);
//	for (int i = 0; i < height; i++) {
//		for (size_t j = 0; j < width; j++) {
//			cout << Pole[i][j];
//		}
//		cout << endl;
//	}
//}
//void Object::Clear(TypePole& pole) {
//	pole[y][x] = ' ';
//}
//void Object::Draw(TypePole& pole) {
//		//cout << getImage();
//		pole[getY()][getX()] = 'E';
//}
bool Object::Logic(TypePole& pole) {
	srand(time(0));
	int dir = Direct(rand() % 4);

	switch (dir) {
	case Left:
		if (pole[y][x - 1] != '#') {
			if (pole[y][x - 1] == '*') { pole[y][x] = '*'; }
			else pole[y][x] = ' ';
			x--;
			pole[y][x] = 'E';
		}
		break;
	case Right:
		if (pole[y][x + 1] != '#') {
			if (pole[y][x+1] == '*') { pole[y][x] = '*'; }
			else { pole[y][x] = ' '; }
			x++; 
			pole[y][x] = 'E';
		}
		break;
	case Up:
		if (pole[y - 1][x] != '#') {
			if (pole[y - 1][x] == '*') { pole[y][x] = '*'; }
			else { pole[y][x] = ' '; }
			y--;
			pole[y][x] = 'E';
		}
		break;
	case Down:
		if (pole[y + 1][x] != '#') {
			if (pole[y + 1][x] == '*') { pole[y][x] = '*'; }
			else { pole[y][x] = ' '; }
			y++;
			pole[y][x] = 'E';
		}
		break;
	}
	return true;
}


Player::Player() :lifes(3), Rage(false), Object() {}
Player::Player(int x, int y, char Image, int lifes) :lifes(lifes), Rage(false), Object(x, y, Image) {}
int Player::getX() const { return x; }
int Player::getY() const { return y; }
int Player::getOldX() const { return OldX; }
int Player::getOldY() const { return OldY; }

int Player::getLifes() const { return lifes; }
char Player::getImage() const { return Image; }
int Player::getRage() const { return Rage; }

void Player::setX(int x) { this->x = x; }
void Player::setY(int y) { this->y = y; }
void Player::setOldX(int x) { this->OldX = x; }
void Player::setOldY(int y) { this->OldY = y; }
void Player::setDir(int dir) { this->dir = dir; }

void Player::setLifes(int lifes) { this->lifes = lifes; }
void Player::setImage(char Image) { this->Image = Image; }
void Player::setRage(int boost) { this->Rage = boost; }

bool Player::Logic(TypePole& pole, int& score) {
	if (lifes == 0) return false;
	if (_kbhit()) {
		dir = _getch();
	}

	switch (dir) {
	case LEFT:
		if (pole[y][x - 1] != '#') {
			if (pole[y][x - 1] == '*') { score++; }
			else if (pole[y][x - 1] == '%') { setRage(getRage() + 1); score=score+5; }
			pole[y][x] = ' ';
			x--;
			pole[y][x] = '&';
		}
		break;
	case RIGHT:
		if (pole[y][x + 1] != '#') {
			if (pole[y][x + 1] == '*') { score++; }
			else if (pole[y][x + 1] == '%') { setRage(getRage() + 1); score = score + 5; }
			pole[y][x] = ' ';
			x++;
			pole[y][x] = '&';
		}
		break;
	case UP:
		if (pole[y-1][x] != '#') {
			if (pole[y - 1][x] == '*') { score++; }
			else if (pole[y - 1][x] == '%') { setRage(getRage() + 1); score = score + 5; }
			pole[y][x] = ' ';
			y--;
			pole[y][x] = '&';
		}
		break;
	case DOWN:
		if (pole[y + 1][x] != '#') {
			if (pole[y + 1][x] == '*') { score++; }
			else if (pole[y + 1][x] == '%') { setRage(getRage() + 1); score = score + 5; }
			pole[y][x] = ' ';
			y++;
			pole[y][x] = '&';
		}
		break;
	case SPACE:
		y = y;
		x = x;
		// Остановка
		break;
	default:
		break;
	}
	return true;
}
//void Player::Draw(TypePole& pole) {
//	//cout << getImage();
//	pole[getY()][getX()] = '&';
//}



// ========= Ghost =============
Ghost::Ghost() : playing(false), Object() {}
Ghost::Ghost(int x, int y, char Image) : playing(false), Object(x, y, Image) {}
bool Ghost::getPlaying() const { return playing; }
void Ghost::setPlaying(bool playing) { this->playing = playing; }

int Ghost::getX() const { return x; }
int Ghost::getY() const { return y; }
int Ghost::getOldX() const { return OldX; }
int Ghost::getOldY() const { return OldY; }

char Ghost::getImage() const { return Image; }

void Ghost::setX(int x) { this->x = x; }
void Ghost::setY(int y) { this->y = y; }
void Ghost::setOldX(int x) { this->OldX = x; }
void Ghost::setOldY(int y) { this->OldY = y; }

void Ghost::setImage(char Image) { this->Image = Image; }
bool Ghost::Logic(TypePole& pole) {
			int dir = Direct(rand() % 4);
			bool mind = rand() % 20;
			if(!mind){
					if (pole[y][x - 1] != '#' && pole[y + 1][x] != '#' && pole[y - 1][x] != '#' && pole[y + 1][x] != '#') {
		dir = Direct(rand() % 4);
	}
					//3 Свободных ячеек
					else if (pole[y][x - 1] != '#' && pole[y + 1][x] != '#' && pole[y - 1][x] != '#') { //Есть пути на Верх Вниз В Лева
						int tMasDir[3] = { Direct::Left, Direct::Up,  Direct::Down };
						dir = tMasDir[rand()%3];
					}
					else if (pole[y][x - 1] != '#' && pole[y][x + 1] != '#' && pole[y - 1][x] != '#') {
		int tMasDir[3] = { Direct::Up, Direct::Left, Direct::Right };
		dir = tMasDir[rand() % 3];
	}
					else if (pole[y+1][x] != '#' && pole[y][x + 1] != '#' && pole[y - 1][x] != '#') {
		int tMasDir[3] = { Direct::Up, Direct::Right, Direct::Down };
		dir = tMasDir[rand() % 3];
	}
					else if (pole[y][x + 1] != '#' && pole[y][x - 1] != '#' && pole[y + 1][x] != '#') {
		int tMasDir[3] = { Direct::Left, Direct::Right, Direct::Down };
		dir = tMasDir[rand() % 3];
	}
					//2 Свободных ячеек 180Град
					else if (pole[y][x + 1] != '#' && pole[y][x - 1] != '#') {
		int tMasDir[2] = { Direct::Left, Direct::Right };
		dir = tMasDir[rand() % 2];
	}
					else if (pole[y - 1][x] != '#' && pole[y + 1][x] != '#') {
		int tMasDir[2] = { Direct::Up, Direct::Down };
		dir = tMasDir[rand() % 2];
	}
					//2 Свободных ячеек 90Град
					else if (pole[y - 1][x] != '#' && pole[y][x + 1] != '#') {
		int tMasDir[2] = { Direct::Up, Direct::Right };
		dir = tMasDir[rand() % 2];
	}
					else if (pole[y][x+1] != '#' && pole[y-1][x] != '#') {
		int tMasDir[2] = { Direct::Right, Direct::Down };
		dir = tMasDir[rand() % 2];
	}
					else if (pole[y + 1][x] != '#' && pole[y][x - 1] != '#') {
		int tMasDir[2] = { Direct::Left, Direct::Down };
		dir = tMasDir[rand() % 2];
	}
					else if (pole[y - 1][x] != '#' && pole[y][x - 1] != '#') {
		int tMasDir[2] = { Direct::Left, Direct::Up };
		dir = tMasDir[rand() % 2];
	}
					//1 направление
					else if (pole[y - 1][x] != '#') { dir = Direct::Up; }
					else if (pole[y + 1][x] != '#') { dir = Direct::Down; }
					else if (pole[y][x-1] != '#') { dir = Direct::Left; }
					else if (pole[y][x+1] != '#') { dir = Direct::Right; }
			}
			switch (dir) {
	case Left:
		if (pole[y][x - 1] != '#') {
			if (pole[y][x - 1] == '*') { pole[y][x] = '*'; }
			else if (pole[y][x - 1] == '%') { pole[y][x] = '%'; }
			else if (pole[y][x - 1] == '@') { pole[y][x++] = '@'; }
			else pole[y][x] = ' ';
			x--;
			pole[y][x] = '@';
		}
		break;
	case Right:
		if (pole[y][x + 1] != '#') {
			if (pole[y][x + 1] == '*') { pole[y][x] = '*'; }
			else if (pole[y][x + 1] == '%') { pole[y][x] = '%'; }
			else if (pole[y][x + 1] == '@') { pole[y][x--] = '@'; }
			else  { pole[y][x] = ' '; }
			x++;
			pole[y][x] = '@';
		}
		break;
	case Up:
		if (pole[y - 1][x] != '#') {
			if (pole[y - 1][x] == '*') { pole[y][x] = '*'; }
			else if (pole[y-1][x] == '%') { pole[y][x] = '%'; }
			else if (pole[y-1][x] == '@') { pole[y++][x] = '@'; }
			else { pole[y][x] = ' '; }
			y--;
			pole[y][x] = '@';
		}
		break;
	case Down:
		if (pole[y + 1][x] != '#') {
			if (pole[y + 1][x] == '*') { pole[y][x] = '*'; }
			else if (pole[y+1][x] == '%') { pole[y][x] = '%'; }
			else if (pole[y+1][x] == '@') { pole[y--][x] = '@'; }
			else { pole[y][x] = ' '; }
			y++;
			pole[y][x] = '@';
		}
		break;
	}
			return true;
}
//void Ghost::Draw(TypePole& pole) {
//	//cout << getImage();
//	pole[getY()][getX()] = '@';
//}