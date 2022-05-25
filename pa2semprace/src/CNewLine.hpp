#pragma once
#include "ncurses.h"
#include "CCell.hpp"


class CNewLine : public CCell
{
    public:
    CNewLine(char c);
    virtual void draw(WINDOW * map);
};
