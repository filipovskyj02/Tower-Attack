#pragma once
#include "ncurses.h"
#include "CCell.hpp"


class CExit : public CCell
{
    public:
    CExit();
    virtual void draw(WINDOW * map);
};
