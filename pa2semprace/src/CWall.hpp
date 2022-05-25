#pragma once
#include "ncurses.h"
#include "CCell.hpp"


class CWall : public CCell
{
    public:
    CWall(char c);
    virtual void draw(WINDOW * map);
};
