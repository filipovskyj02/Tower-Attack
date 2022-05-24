#pragma once
#include "vector"
#include "ncurses.h"
#include "iostream"
#include "CMap.hpp"
#define WIDTH_MULTI 2.5
#define MENU_ITEM_DISTANCE 2
#define SCREEN_POS 2.5
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
public:
    CGame(int collum_height, int row_width);
    void InfoRefresh(WINDOW * InfoBar);
   
    
    
    



};


