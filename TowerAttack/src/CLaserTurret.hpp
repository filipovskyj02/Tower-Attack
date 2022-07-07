#pragma once
#include "ncurses.h"
#include "CTower.hpp"
#include "SConf.hpp"



class CLaserTurret : public CTower
{
    public:
    CLaserTurret(int x, int y, TowerConf & a);
    
    virtual void draw(WINDOW * map);
    virtual void attack(CAttacker * enemy);
    
   
};