//
// Pacman.h
//

#pragma once

#include <iostream>
#include <time.h>    // clock(), time()
#include <conio.h> // _kbhit()  _getch()
#include <Windows.h>
#include <vector>
#include <string>

#include "Win10.h"



class Object {
protected:
  int x, y;
  int OldX, OldY;
  char Image;
public:
  Object();
  Object(int x, int y, char Image);

  virtual int getX() const;
  virtual int getY() const;
  virtual int getOldX() const;
  virtual int getOldY() const;
  virtual char getImage() const;

  virtual void setX(int x);
  virtual void setY(int y);
  virtual void setOldX(int x);
  virtual void setOldY(int y);
  virtual void setImage(char Image);
  //void Draw();
  //virtual void Clear(TypePole& pole);
  //virtual void Draw(TypePole& pole);
  virtual bool Logic(TypePole& pole);
};

class Player : protected Object {
protected:
  int lifes;
  int dir = 0;
  int Rage;
public:
  Player();
  Player(int x, int y, char Image, int lifes);

  virtual int getX() const;
  virtual int getY() const;
  virtual int getOldX() const;
  virtual int getOldY() const;
  virtual int getLifes() const;
  virtual char getImage() const;
  virtual int getRage() const;

  virtual void setX(int x);
  virtual void setY(int y);
  virtual void setOldX(int x);
  virtual void setOldY(int y);
  virtual void setDir(int dir);

  virtual void setLifes(int lifes);
  virtual void setImage(char Image);
  virtual void setRage(int boost);

  virtual bool Logic(TypePole& pole, int& score);
  //virtual void Draw(TypePole& pole);
};

class Ghost : virtual public Object {
  bool playing;
public:
  Ghost();
  Ghost(int x, int y, char Image);

  virtual bool getPlaying() const;
  virtual void setPlaying(bool playing);

  virtual int getX() const;
  virtual int getY() const;
  virtual int getOldX() const;
  virtual int getOldY() const;
  virtual char getImage() const;

  virtual void setX(int x);
  virtual void setY(int y);
  virtual void setOldX(int x);
  virtual void setOldY(int y);

  virtual void setImage(char Image);
  virtual bool Logic(TypePole& pole);

  //virtual void Draw(TypePole& pole);
};