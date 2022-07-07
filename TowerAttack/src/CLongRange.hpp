#pragma once
#include "ncurses.h"
#include "CAttacker.hpp"
#include "SConf.hpp"

struct AttackerConf;

class CLongRange : public CAttacker
{
    public:
    CLongRange(int x, int y,AttackerConf & a);
    
    virtual void draw(WINDOW * map);
    virtual void move(void);
    virtual void attack(CTower * enemy);
    virtual char whatToFind();
};
