#pragma once

#include "vector"
#include "ncurses.h"
#include "iostream"
#include <fstream>
#include "CCell.hpp"
#include "memory"
#include "CCellBasic.hpp"
#include "CAttacker.hpp"
#include "CTower.hpp"
#include "CHogRider.hpp"
#include "CLaserTurret.hpp"
#include "CMapScout.hpp"
#include "CTank.hpp"



class CMap
{
    public:
    int sizeX;
    int sizeY;
    WINDOW * mapWin;
    std::vector<std::unique_ptr<CCell>> mapVec;
    std::vector<std::unique_ptr<CAttacker>> DynamicVec;
    std::vector<std::unique_ptr<CTower>> TowerVec;
    std::vector<unsigned int> EnteranceCords;
    std::vector<unsigned int> ExitCords;
    int enteranceSel;
    int enteranceCnt;


    CMap();
    
    void redraw(WINDOW * win);
    void loadMap(int & loadedX, int  & loadedY);
    void buy(int index);
    void enteranceUp();
    void enteranceDown();
    void calculatePath( CAttacker * a, char lookingFor);
    void placeTowers(int n);
    void towerFire();
    
 
};


