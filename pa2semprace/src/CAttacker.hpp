#pragma once
#include "ncurses.h"
#include "vector"
#include "CTower.hpp"

class CTower;

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
    int fullHealth;
    int range;
    int fireFrequency;
    int shotsCnt;
    bool dead;
    
    
     
    virtual void draw(WINDOW * map) = 0;
    virtual void move(void) = 0;
    virtual void attack(CTower * enemy) = 0;
    virtual char whatToFind() = 0;

};