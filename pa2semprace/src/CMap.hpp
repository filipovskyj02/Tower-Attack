#pragma once

#include "vector"
#include "ncurses.h"
#include "iostream"
#include <fstream>
#include "CCell.hpp"
#include "memory"
#include "CAir.hpp"
#include "CWall.hpp"
#include "CNewLine.hpp"
#include "CEnterance.hpp"
#include "CExit.hpp"
#include "CAttacker.hpp"
#include "CHogRider.hpp"



class CMap
{
    int sizeX;
    int sizeY;
    WINDOW * mapWin;
    std::vector<std::unique_ptr<CCell>> mapVec;
    std::vector<std::unique_ptr<CAttacker>> DynamicVec;
    std::vector<unsigned int> EnteranceCords;
    int enteranceSel;
    int enteranceCnt;

public:
    CMap();
    CMap(int y, int x, WINDOW * mapWin);
    void redraw(WINDOW * win);
    void loadMap();
    void buy(int index);
    void enteranceUp();
    void enteranceDown();
 

};


