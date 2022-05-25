#pragma once
#include "ncurses.h"

//#include "CWall.hpp"


class CCell{
    public:
    char C;
    CCell(char C);
    CCell();
    
     
    virtual void draw(WINDOW * map) = 0;

};