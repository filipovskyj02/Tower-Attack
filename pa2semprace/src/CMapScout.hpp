#pragma once
#include "ncurses.h"
#include "CAttacker.hpp"


class CMapScout : public CAttacker
{
    public:
    CMapScout(int x, int y);
    virtual void draw(WINDOW * map);
    virtual int speed(void);
    virtual void move(void);
    
  
};