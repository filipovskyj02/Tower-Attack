#pragma once
#include "ncurses.h"
#include "CCell.hpp"


class CAir : public CCell
{
    public:
    CAir(char c);
    virtual void draw(WINDOW * map);
};
