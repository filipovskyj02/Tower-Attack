#pragma once

#include "vector"
#include "ncurses.h"
#include "iostream"


class CMap
{
    int sizeX;
    int sizeY;
    WINDOW * mapWin;
    std::vector<char> map;
public:
    CMap();
    CMap(int y, int x, WINDOW * win);
 



};


