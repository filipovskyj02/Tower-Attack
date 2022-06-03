#pragma once
#include "vector"
#include "ncurses.h"
#include "iostream"
#include "CMap.hpp"
#include "chrono"
#include "thread"

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
public:
    CGame();
    CGame(int collum_height, int row_width, int mapChoice);
    void InfoRefresh(WINDOW * InfoBar);
    void redraw(WINDOW * mapWin);
   
    
    
    



};


