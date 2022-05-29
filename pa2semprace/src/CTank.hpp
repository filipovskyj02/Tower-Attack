#pragma once
#include "ncurses.h"
#include "CAttacker.hpp"


class CTank : public CAttacker
{
    public:
    CTank(int x, int y);
    
    virtual void draw(WINDOW * map);
    virtual int speed(void);
    virtual void move(void);
};
