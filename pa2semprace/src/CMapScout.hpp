#pragma once
#include "ncurses.h"
#include "CAttacker.hpp"


class CMapScout : public CAttacker
{
    public:
    CMapScout(int x, int y);
    virtual void draw(WINDOW * map);
    virtual void move(void);
    virtual void attack(CTower * ememy);
    virtual char whatToFind();
         



    
  
};