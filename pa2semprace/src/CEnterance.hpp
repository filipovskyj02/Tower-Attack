#pragma once
#include "ncurses.h"
#include "CCell.hpp"


class CEnterance : public CCell
{
    public:
    bool selected;
    CEnterance();
    virtual void draw(WINDOW * map);
};
