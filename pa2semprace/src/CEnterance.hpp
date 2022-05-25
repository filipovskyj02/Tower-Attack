#pragma once
#include "ncurses.h"
#include "CCell.hpp"


class CEnterance : public CCell
{
    public:
    CEnterance();
    virtual void draw(WINDOW * map);
};
