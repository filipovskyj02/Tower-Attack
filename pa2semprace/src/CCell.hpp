#pragma once
#include "ncurses.h"
#include "utility"




class CCell{
    public:
    char C;
    CCell(char C, int total, int x, int y);
    CCell();
    virtual void draw(WINDOW * map) = 0;
    int xCord;
    int yCord;
    int Index;
    int towerIndex;
    int AttackerIndex;
    int healthDraw;
    
    std::pair<int,int> pathIndex;

};