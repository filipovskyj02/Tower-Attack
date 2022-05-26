#pragma once
#include "ncurses.h"
#include "CAttacker.hpp"


class CHogRider : public CAttacker
{
    public:
    CHogRider(int x, int y);
    virtual void draw(WINDOW * map);
    virtual int speed(void);
    virtual void move(void);
};
