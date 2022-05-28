#pragma once
#include "ncurses.h"
#include "CTower.hpp"


class CLaserTurret : public CTower
{
    public:
    CLaserTurret(int x, int y);
    
    virtual void draw(WINDOW * map);
   
};