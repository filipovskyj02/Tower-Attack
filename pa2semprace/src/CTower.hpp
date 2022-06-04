#pragma once
#include "ncurses.h"
#include "vector"
#include "CAttacker.hpp"



//fixes circular dependency linker error
class CAttacker;

class CTower{
    public:
    char C;
    CTower(int x, int y);
    CTower();
    int x;
    int y;
    int damage;
    int range;
    int fireFrequency;
    int shotsCnt;
    int health;
    int fullHealth;
    bool destroyed;
    int towerIndex;
   
    virtual void draw(WINDOW * map) = 0;
    virtual void attack(CAttacker * enemy) = 0;
    

};