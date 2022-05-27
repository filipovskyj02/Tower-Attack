#pragma once
#include "ncurses.h"
#include "string"
#include "vector"
#include "iostream"
#include <filesystem>



#define WIDTH_MULTI 2.5
#define MENU_ITEM_DISTANCE 10
#define SCREEN_POS 2.5

class CMenu
{
    
private:
    int maxW,maxH;
    bool continueToGame;
    
public:
    CMenu(int p_width,int p_height);
    void help (WINDOW * MenuWin);
    bool contin();
    
    
};

