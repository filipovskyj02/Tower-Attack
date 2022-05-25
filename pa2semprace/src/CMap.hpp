#pragma once

#include "vector"
#include "ncurses.h"
#include "iostream"
#include <fstream>


class CMap
{
    int sizeX;
    int sizeY;
    WINDOW * mapWin;
    std::vector<char> mapVec;
    int redrawCnt;
public:
    CMap();
    CMap(int y, int x, WINDOW * mapWin);
    void redraw(WINDOW * win);
    void loadMap();
 

};


