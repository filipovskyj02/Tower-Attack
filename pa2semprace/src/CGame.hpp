#pragma once
#include "vector"
#include "ncurses.h"
#include "iostream"
#include "CMap.hpp"
#include "chrono"
#include "thread"
#include "sstream"
#include "string"
#include "SConf.hpp"

#define MENU_ITEM_DISTANCE 2

#define MENU_HEIGHT 5
#define INFO_HEIGHT 5



class CGame
{
    int row_width;
    int collum_height;
    bool isOver;
    CMap gameMap;
    int playerMoney;
    int ScreenX;
    int ScreenY;
    int mapChoice;
    bool waiting;
public:
    CGame();
    CGame(int mapChoice, int confChoice);
    void InfoRefresh(WINDOW * InfoBar);
    void redraw(WINDOW * mapWin);
    bool escOptions(WINDOW * mapWin);
    void parseFile(int confChoice);
    std::string readTillSpace(std::string & in, int & index, std::ofstream & of);
    std::vector<std::pair<std::string,std::string>> NameCost;
    std::vector<AttackerConf> att;
    std::vector<TowerConf> tww;

};


