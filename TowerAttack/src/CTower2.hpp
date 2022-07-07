#pragma once
#include "ncurses.h"
#include "CTower.hpp"
#include "SConf.hpp"



class CTower2 : public CTower
{
    public:
    CTower2(int x, int y, TowerConf & a);
    
    virtual void draw(WINDOW * map);
    virtual void attack(CAttacker * enemy);
    
   
};
