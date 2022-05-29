#pragma once
#include "ncurses.h"
#include "vector"

//#include "CWall.hpp"


class CAttacker{
    public:
    char C;
    CAttacker(char C);
    CAttacker();
    int x;
    int y;
    int damage;
    int runSpeed;
    std::vector<std::pair<int,int>> path;
    int pathIndex;
    bool left;
    int moveCnt;
    int health;
    
    
     
    virtual void draw(WINDOW * map) = 0;
    virtual int speed(void) = 0;
    virtual void move(void) = 0;

};