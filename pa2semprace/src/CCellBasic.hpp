#pragma once
#include "ncurses.h"
#include "CCell.hpp"


class CAir : public CCell
{
    public:
    CAir(int total, int x, int y);
    virtual void draw(WINDOW * map);
};


class CEnterance : public CCell
{
    public:
    bool selected;
    CEnterance(int total, int x, int y);
    virtual void draw(WINDOW * map);
};

class CExit : public CCell
{
    public:
    CExit(int total, int x, int y);
    virtual void draw(WINDOW * map);
};

class CNewLine : public CCell
{
    public:
    CNewLine(int total, int x, int y);
    virtual void draw(WINDOW * map);
};

class CWall : public CCell
{
    public:
    CWall(int total, int x, int y);
    virtual void draw(WINDOW * map);
};

