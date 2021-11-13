//
// Game.cpp
//

//#include "Game.h"
#include<string>
#include<fstream>

#include "Win10.h"
#include "Menu.h"
#include "Pacman.h"


class Game {
  int       xCol, yRow;   // координаты верхн.-левого угла для вывода поля игры
  Menu      MainMenu;     // экземпляр главного меню игры
  bool      isGame;       // true - если игра началась
  bool      isExit;       // true - если выходим из программы
  int       ColorTxtDef;  // Цвет не выбранного текста
  int       ColorTxtChg;  // Цвет выбранного текста

  int MapLevel;           // Уровень Карты

  int TotalScore;         // Общае колво заработанных очков за всю игру
  int score;              // Очки
  int OldScore;           // Очки при начале игры

  int isRage;             // В Райдже ли он?

  //TypePole Pole;
  Player player;
  Ghost ghost[4];
  int ghostCnt;

  //Карты
  TypePole Pole;
  TypePole OldPole;

  void setScore(int newScore = 0) { score = newScore; }
  int getScore() { return score; }
  void UpScore() { ++score; }
  int getTotalScore() { return TotalScore; }
  void setTotalScore(int newScore) { TotalScore = newScore; }
  int& getOldScore() { return OldScore; }

  void UpMapLevel() { ++MapLevel; }
  void setMapLevel(int Level) { MapLevel = Level; }
  void setPole(TypePole& newPole) {
    Pole.resize(newPole.size());
    for (int i = 0; i < newPole.size(); i++) {
      Game::Pole[i].resize(newPole[i].size());
      for (int j = 0; j < newPole[i].size(); j++) {
        Game::Pole[i][j] = newPole[i][j];
      }
    }
  }
  void setOldPole(TypePole& newPole) {
    OldPole.resize(newPole.size());
    for (int i = 0; i < newPole.size(); i++) {
      Game::OldPole[i].resize(newPole[i].size());
      for (int j = 0; j < newPole[i].size(); j++) {
        Game::OldPole[i][j] = newPole[i][j];
      }
    }
  }
  void setGhostCnt(size_t cnt) {
    if (cnt < 1 || cnt > 4);
    else { ghostCnt = cnt; }
  }
  int getGhostCnt() const { return ghostCnt; }

  int getIsRage() const { return isRage; }
  void setIsRage(int RageCnt) { isRage = RageCnt; }
public:
  Game() : isExit(false), xCol(3), yRow(5), ColorTxtDef(COLOR::_WHITE), ColorTxtChg(COLOR::_GREEN), OldScore(), score(), MapLevel(), ghostCnt(1), TotalScore(), isRage() {
    TypePole Temp
    {
        "###############################              ",
        "#           #     #    #    # # Controls Key ",
        "#    # #### #  #     # # ##   #    Arrows    ",
        "#          *   # ##  #      # #              ",
        "#  &     ##*#          #  @   # Meals:       ",
        "#          *   # ##  #      # #              ",
        "#    # #### #  #     # # ##   #              ",
        "#           #     #    #    # #              ",
        "###############################              ",
        "Level 0                                      "
    };
    //Temp[2][43] = char(26);
    //Temp[3][43] = char(27);
    //Temp[4][43] = char(24);
    //Temp[5][43] = char(25);
    //Temp[8][43] = char(7);
    setPole(Temp);
    setOldPole(Temp);
  }
  //void MenuStart(); // запустить класс Game для начала игры

  const int getMapLevel() const { return MapLevel; }

  bool syncMaps() // Синхранизация Уровней 
  {
    for (int i = 0; i < OldPole.size(); i++) {
      for (int j = 0; j < OldPole[i].size(); j++) {
        Game::Pole[i][j] = Game::OldPole[i][j];
      }
    }
    Setup(); //Установка позиций пакмена и тд
    return true;
  }
  string checkFormat(string& FileName, string Format = ".txt") { //Проверка формата На .txt
    string temp = "";
    if (FileName.size() == 0) {
      cout << "Error FileName.size() == 0";
      FileName = "ErorSave";
    }
    else if (FileName.size() > (Format.size() + 1)) {
      for (int i = FileName.size() - (Format.size()); i < FileName.size(); i++) {
        temp = temp + FileName[i];
      }
    }
    if (temp != Format) {
      FileName = FileName + Format;
    }
    return FileName;
  }
  int CountStrFile(string FileName) { //Метод считывающая колво строк
    ifstream file;
    file.open(FileName);
    int Count = 0;
    string line;
    for (int i = 0; i < 100; i++) {
      if (!file.eof()) std::getline(file, line);
      else if (file.eof()) break;
      Count++;
    }
    file.close();
    return Count - 1;
  }
  void Save(const string& FileName) {
    fstream out(FileName, ios::out);
    TypePole Save;

    out << getScore() << " " << player.getLifes() << endl;

    for (int i = 0; i < Pole.size(); i++) { //i <- Y
      for (int j = 0; j < Pole[i].size(); j++) { //j <- X
        out << Pole[i][j];//Save[j] = Pole[j];
      }
      out << endl;
    }
    out.close();
  }
  bool LoadLevel(string FileName) { //Загрузка уровня при находке проекта возвращает true
    fstream inp(FileName, ios::in);
    if (inp.is_open()) {
      TypePole Save;
      int MapScore;
      inp >> getOldScore();
      setScore(getOldScore());

      int Count;
      inp >> Count;
      player.setLifes(Count);//Присваивание жизней
      //cout << "LivesPlayer: " << livesPlayer;

      string line = "";
      getline(inp, line); //Пропуск цифр которые озночают очки и жизни 

      Pole.resize(CountStrFile(FileName));
      OldPole.resize(CountStrFile(FileName));
      for (int i = 0; i < CountStrFile(FileName); i++) { //Загрузка уровня с обновлением карт
        getline(inp, line);
        OldPole[i].clear();
        Pole[i].resize(line.size());
        OldPole[i].resize(line.size());
        for (int j = 0; j < Pole[i].size(); j++) {
          Pole[i][j] = OldPole[i][j] = line[j];
        }
        cout << Pole[i] << endl;
      }
      Setup(); //Установка позиций пакмена и тд
      cout << "Success Load level: " << FileName;
      Sleep(1000);
    }
    else { cout << FileName << " Not Found!"; Sleep(1000);  return false; }
    system("cls");
    inp.close();
    return true;
  }
  bool NextLevel() {
    //SetPos((xCol + Pole[0].size() / 2)-7, (yRow + Pole.size() / 2)-2);
    SetPos(xCol, yRow);
    SetColor(COLOR::_BLUE);
    cout << "- = YOU WIN! = -";
    Sleep(1000);
    UpMapLevel();
    string NameLevel = "Level_", lvl;

    if (getMapLevel() > 9 && getMapLevel() < 100) {
      int num = getMapLevel(), tens = 100, temp;
      for (int i = 0; i < 2; i++) {
        temp = num % tens;
        tens = tens / 10;
        lvl = lvl + char(temp + 48);
      }
    }
    else {
      lvl = char(getMapLevel() + 48);
    }
    NameLevel = "Level_" + lvl;
    ifstream file(checkFormat(NameLevel));
    if (!file.is_open()) {   // Файл не найден
      file.close();
      //SetPos((xCol + Pole[0].size() / 2) - 7, (yRow + Pole.size() / 2) - 2);
      SetPos(xCol, yRow);
      SetColor(COLOR::_RED);
      cout << "- = Game Over = -";
      setMapLevel(getMapLevel() - 1);
      Sleep(1000);
    }
    else if (file.is_open()) { // Файл найден
      for (int i = 0; i < 3; i++) {
        //SetPos((xCol + Pole[0].size() / 2) - 7, (yRow + Pole.size() / 2) - 2);
        SetPos(xCol, yRow);
        SetColor(i + 2);
        cout << "- = " << NameLevel << " = -";
        Sleep(1500 / 3);
      }
      SetColor(ColorTxtDef);
      system("cls");
      return LoadLevel(checkFormat(NameLevel));; //Уровень загружен
    }
    SetColor(ColorTxtDef);
    system("cls");
    return false; //Загрузка уровня
  }

  bool SaveScore() {
    system("cls");
    SetPos(xCol, yRow);
    cout << "Do you want to save your score?";
    Menu MenuSavePers("Yes!", COLOR::_WHITE, COLOR::_YELLOW, xCol, yRow + 1); // Поменять местами
    MenuSavePers.addTitle("No :(");
    while (!isExit) {
      MenuSavePers.Show();
      switch (_getch()) {
      case UP:
        MenuSavePers.UpSelect();
        break;
      case DOWN:
        MenuSavePers.DownSelect();
        break;
      case ENTER:
        if (MenuSavePers.getSelect() == MenuSavePers.getSelect("Yes!")) { // Да
          system("cls");
          SetPos(xCol, yRow);
          cout << "Enter your name: ";
          string name;
          cin >> name;
          cin.ignore();
          ifstream file("Leaderboard.txt");
          if (file.is_open()) {
            fstream writeFile("Leaderboard.txt", ios::app);
            cout << name << "\t" << getTotalScore() << "\t" << getMapLevel() << " lvl\n";
            writeFile << name << "\t" << getTotalScore() << "\t" << getMapLevel() << " lvl\n";
            writeFile.close();
          }
          else {
            fstream writeFile("Leaderboard.txt", ios::out);
            cout << name << "\t" << getTotalScore() << "\t" << getMapLevel() << " lvl\n";
            writeFile << name << "\t" << getTotalScore() << "\t" << getMapLevel() << " lvl\n";
            writeFile.close();
          }
          file.close();
          Sleep(1000);
          system("cls");
          return true;
        }
        else if (MenuSavePers.getSelect() == MenuSavePers.getSelect("No :(")) {// нет но я все таки сохраню
          ifstream file("Leaderboard.txt");
          if (file.is_open()) {
            fstream writeFile("Leaderboard.txt", ios::app);
            cout << "Player\t" << getTotalScore() << "\t" << getMapLevel() << " lvl\n";
            writeFile << "Player\t" << getTotalScore() << "\t" << getMapLevel() << " lvl\n";
            writeFile.close();
          }
          else {
            fstream writeFile("Leaderboard.txt", ios::out);
            cout << "Player\t" << getTotalScore() << "\t" << getMapLevel() << " lvl\n";
            writeFile << "Player\t" << getTotalScore() << "\t" << getMapLevel() << " lvl\n";
            writeFile.close();
          }
          file.close();
          Sleep(1000);
          system("cls"); 
          return true;
        }
        break;
      case ESC:
        system("cls");
        SetColor(COLOR::_RED);
        SetPos(xCol, yRow);
        cout << "You didn't save it!";
        Sleep(1000);
        system("cls");
        return false;
        break;
      default:
        break;
      }
    }

  } // показать главное меню игры

  void ShowMainMenu() // Меню Игры
  {
    MainMenu.addTitle("New Game");
    MainMenu.addTitle("Continue");
    MainMenu.addTitle("Load Level");
    MainMenu.addTitle("Leaderboard");
    MainMenu.addTitle("About");
    MainMenu.addTitle("Exit");

    MainMenu.setPos(xCol, yRow);
    MainMenu.setColorTxtDef(ColorTxtDef);
    MainMenu.setColorTxtChg(ColorTxtChg);

    while (!isExit) {
      MainMenu.Show();
      switch (_getch()) {
      case UP:
        MainMenu.UpSelect();
        break;
      case DOWN:  
        MainMenu.DownSelect();
        break;
      case ENTER:
        if (MainMenu.getSelect() == MainMenu.getSelect("New Game")) { // Начать игру с начало
          //syncMaps();
          setMapLevel(0);
          if (!LoadLevel("Level_0.txt")) { player.setLifes(3); }
          StartGame();
        }
        else if (MainMenu.getSelect() == MainMenu.getSelect("Continue")) {// Продолжить игру
          LoadLevel("Continue.txt");
          StartGame();
        }
        else if (MainMenu.getSelect() == MainMenu.getSelect("Load Level")) { // Начать игру с начало
          system("cls");
          SetPos(xCol, yRow);
          cout << "Enter file name(without .txt): ";
          string FileName;
          cin >> FileName;
          if (LoadLevel(checkFormat(FileName))) {
            //syncMaps(); //Synh
            system("cls");
            StartGame(); 
          }
          system("cls");
        }
        else if (MainMenu.getSelect() == MainMenu.getSelect("Leaderboard")) {// Таблица лидеров
          system("cls");
          SetPos(xCol, yRow);
          
          ifstream file("Leaderboard.txt");
          if (file.is_open()) {
            cout << "Name\tScore\tLevel";
            string line;
            int index = 0;
            while (!file.eof()) {
              if (index == 0) { SetColor(COLOR::_YELLOW); Sleep(500); }
              else if (index == 1) {SetColor(COLOR::_LIGHT_PURPLE); Sleep(500);}
              else if (index == 2) { SetColor(COLOR::_LIGHT_BLUE); Sleep(500); }
              else SetColor(COLOR::_WHITE);
              SetPos(xCol, yRow + ++index);
              getline(file, line);
              cout << line << '\n';
            }
            system("pause");
          }
          else { 
            cout << "File: \"Leaderboard.txt not Found\"!"; 
            Sleep(1500); 
          }
          file.close();
          SetColor(COLOR::_WHITE);
          system("cls");
        }
        else if (MainMenu.getSelect() == MainMenu.getSelect("About")) {// About
          About();
        }
        else if (MainMenu.getSelect() == MainMenu.getSelect("Exit")) { // Выход
          MenuExit();
        }

        break;
      case ESC:
        MenuExit();
        break;
      default:
        break;
      }
    }

  } // показать главное меню игры
  bool MenuExit() // Меню Выхода // Интересный факт Если оно что не возвращает то выходит 
  {
    Menu Exit("No ", ColorTxtDef, ColorTxtChg, xCol + 2, yRow + 2);
    bool inThis = true;
    Exit.addTitle("Yes");

    system("cls");
    while (inThis)
    {
      SetPos(xCol, yRow);
      cout << "Exit Game?";

      Exit.Show();
      switch (_getch()) {
      case UP:
        Exit.UpSelect();
        break;
      case DOWN:
        Exit.DownSelect();
        break;
      case ENTER: {
        if (Exit.getSelect() == 0) {
          return isExit = inThis = false;
        }
        else if (Exit.getSelect() == 1) {
          inThis = false;
          return isExit = true;
        }
        else { cout << "Error Game::MenuExit()"; }
      }
                break;
      case ESC:
        return isExit = inThis = false;
        break;
      default:
        break;
      }
    }
  }//Выход?
  bool MenuGame() {
    Menu MenuInGame("Continue", ColorTxtDef, ColorTxtChg, xCol, yRow);
    MenuInGame.addTitle("Restart");
    MenuInGame.addTitle("Load Level");
    MenuInGame.addTitle("Save");
    MenuInGame.addTitle("Go Menu");

    while (!isExit) {
      MenuInGame.Show();
      switch (_getch()) {
      case UP:
        MenuInGame.UpSelect();
        break;
      case DOWN:
        MenuInGame.DownSelect();
        break;
      case ENTER:
        if (MenuInGame.getSelect() == MenuInGame.getSelect("Continue")) { // Продолжить
          system("cls");
          return true;
        }
        else if (MenuInGame.getSelect() == MenuInGame.getSelect("Restart")) {// Начать с начало
            //Перезапись уровня до начального состояния
          syncMaps();
          setScore(getOldScore());
          player.setLifes(3);
          system("cls");
          //clear();
          return true;
        }
        else if (MenuInGame.getSelect() == MenuInGame.getSelect("Save")) { // Сохранить
          system("cls");
          SetPos(xCol, yRow);
          cout << "Enter Name Save (witout txt): ";
          string FileName;
          cin >> FileName;
          Save(checkFormat(FileName));
          //system("cls");
        }
        else if (MenuInGame.getSelect() == MenuInGame.getSelect("Load Level")) {// Выбрать уровень
          system("cls");
          SetPos(xCol, yRow);
          cout << "Enter Name Save (witout txt): ";
          string FileName;
          cin >> FileName;
          LoadLevel(checkFormat(FileName));
          return true; 
        }
        else if (MenuInGame.getSelect() == MenuInGame.getSelect("Go Menu")) { // Выход в меню
          Save("Continue.txt");
          system("cls");
          return false;
        }

        break;
      case ESC:
        system("cls");
        return true;
        break;
      default:
        break;
      }
    }
  }
  void About() {
    system("cls");
    int pos = 0;
    SetColor(ColorTxtChg);
    SetPos(xCol, yRow + pos++);
    cout << "Exam Project Pacman";

    SetPos(xCol, yRow + ++pos);
    SetColor(ColorTxtChg);
    cout << "Game Developers:";
    SetColor(ColorTxtDef);
    SetPos(xCol + 1, yRow + ++pos);
    cout << "Kappasov Dias";
    SetPos(xCol + 1, yRow + ++pos);
    cout << "Shalkarov Temirlan";
    SetPos(xCol + 1, yRow + ++pos);
    cout << "Rakhmangali Damir";

    SetColor(ColorTxtChg);
    SetPos(xCol, yRow + ++++pos);
    cout << "Made Data: ";
    SetColor(ColorTxtDef);
    cout << "13D 05M 2020Y 5AM";

    SetColor(ColorTxtChg);
    SetPos(xCol, yRow + ++++pos);
    cout << "Pacman: ";
    SetColor(ColorTxtDef);
    cout << "1.0 (Final Version)";
    WaitPause(30000);
    system("cls");
  }

  void Draw() {
    SetPos(0, 0);
    for (int i = 0; i < Pole.size(); i++) {
      for (size_t j = 0; j < Pole[i].size(); j++) {
  
        if (Pole[i][j] == '#') {
          //Pole[i][j] = char(219);
          SetColor(COLOR::_GRAY);
          cout << char(219);
        }
        else if (Pole[i][j] == '*') {
          SetColor(COLOR::_WHITE);
          cout << '.';
        }
        else if (Pole[i][j] == '%') {
          SetColor(COLOR::_RED);
          cout << '%';
        }
        else if (Pole[i][j] == '@') {
          if (player.getRage()) { SetColor(rand() % 3+1); }
          else SetColor(COLOR::_LIGHT_BLUE);;
          cout << char(1);//locGhost.getImage();
        }
        else if (Pole[i][j] == '&') {
          if (player.getRage()) { SetColor(((rand()%2)?COLOR::_YELLOW:COLOR::_LIGHT_YELLOW)); }
          else SetColor(COLOR::_YELLOW);
          
          cout << char(2);//locPlayer.getImage();
        }
        else {
          SetColor(COLOR::_WHITE);
          cout << Pole[i][j];
        }
      }
      cout << '\n';
    }
    SetColor(COLOR::_RED);
    cout << char(3);
    SetColor(COLOR::_WHITE);
    cout << ':' << player.getLifes() << "\t" << "SCORE: " << getScore() << ' ';
  }
  
  void Setup() { // Вот тут возможно ошибка Игрок и призрак сохраняют свою старые места
    player.setDir(SPACE);
    int ghostIndex = 0;
    for (int i = 0; i < Pole.size(); i++) {// Установка обьектов по карте
      for (int j = 0; j < Pole[i].size(); j++) {
        if (Pole[i][j] == '@') {
          ghost[ghostIndex].setOldX(j);
          ghost[ghostIndex].setOldY(i);
          ghost[ghostIndex].setX(ghost[ghostIndex].getOldX());
          ghost[ghostIndex].setY(ghost[ghostIndex].getOldY());
          setGhostCnt(++ghostIndex);
        }
        else if (Pole[i][j] == '&') {
          player.setOldX(j);
          player.setOldY(i);
          player.setX(player.getOldX());
          player.setY(player.getOldY());
        }
      }
    }
    player.setRage(0); // Убираем эффекты 
    setIsRage(0); // Убираем эффекты 
    //setTotalScore(getScore() + getTotalScore()); // Для сохранения 
    setScore(getOldScore()); // Присваеваем для карты  
  }

  void StartGame() { //Start Game 
    system("cls");
    bool gameOver = false;
    //int isRage = 0;
    //clock_t startTimer = 0; // начало в милисекундах
    clock_t endTimer = 0; // конец в милисекундах
    //int score;
    //int oldX, oldY;
    //Player player;
    //Ghost ghost;
    player.setImage(char(2));
    for (int i = 0; i < getGhostCnt()-1; i++) {
      ghost[i].setImage(char(1));
    }
    Setup();
    while (!gameOver) {
      if (_kbhit()) { // Выход в меню
        if (_getch() == ESC) {
          gameOver = !MenuGame();
        }
      }

      //player.Logic(Pole, score);
      if (player.Logic(Pole, score) == false) { 
        gameOver = true;
        SetPos(xCol, yRow);
        SetColor(COLOR::_RED);
        cout << "- = YOU LOSE = -";
        Sleep(1000);
        setTotalScore(getScore() + getTotalScore()); // Сохранение Обшего колво очков
        SaveScore();
        //Draw(player, ghost, score);
        system("cls");
        break;
      }
      for (int i = 0; i < getGhostCnt(); i++) { // Убиваем?
        ghost[i].Logic(Pole);
        if (ghost[i].getY() == player.getY() && ghost[i].getX() == player.getX() && !player.getRage()) { // Убивает ли призрак?
          player.setLifes(player.getLifes() - 1);
          //Pole[player.getY()][player.getX()] = ' ';
          player.setX(player.getOldX());
          player.setY(player.getOldY());
          if (player.getLifes() != 0) { Pole[player.getOldY()][player.getOldX()] = '&'; }
          player.setDir(ARROW::SPACE);
        }
        else if (ghost[i].getY() == player.getY() && ghost[i].getX() == player.getX() && player.getRage()) {
          ghost[i].setX(ghost[i].getOldX());
          ghost[i].setY(ghost[i].getOldY());//Добавить прорисовку призраков к карте тут если не роботет коректон
          setScore(getScore()+15); // За убийство Призрака присваеваем 15 очков
          //Pole[player.getOldY()][player.getOldX()] = '&';
        }
      }
      
      Draw();

      int CountMeal = 0;
      for (int i = 0; i < Pole.size(); i++) {
        for (int j = 0; j < Pole[i].size(); j++) {
          if (Pole[i][j] == '*') {
            CountMeal++;
            break;
          }
        }
        if (CountMeal > 0) {
          break;
        }
      }
      if (CountMeal == 0) {
        setTotalScore(getScore() + getTotalScore()); // Сохранение общего ковлво очков
        gameOver = !NextLevel();
        if (gameOver == true) { SaveScore(); }
      }

      // Таймер на буст
      if (player.getRage() && player.getRage() != getIsRage()) {
        setIsRage(getIsRage()+1);
        //запуск таймера
        endTimer = clock() + 10000; // конец в милисекундах
      }
      else if (player.getRage() && clock() >= endTimer) { 
        setIsRage(0);
        player.setRage(getIsRage());
      }

      Sleep(150/((player.getRage())?2:1));
    }
    system("cls");
  }
};