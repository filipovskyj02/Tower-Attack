#pragma once
#include "ncurses.h"
#include "vector"




class CTower{
    public:
    char C;
    CTower(int x, int y);
    CTower();
    int x;
    int y;
    int damage;
   
    virtual void draw(WINDOW * map) = 0;
    

};