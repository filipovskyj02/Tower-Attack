#pragma once

#include "vector"
#include "ncurses.h"
#include "iostream"
#include <fstream>
#include "CCell.hpp"
#include "memory"
#include "CCellBasic.hpp"
//#include "CAttacker.hpp"
//#include "CTower.hpp"
#include "CHogRider.hpp"
#include "CLaserTurret.hpp"
#include "CMapScout.hpp"
#include "CTank.hpp"

#define TOWER_LETTER 'T'
#define EXIT_LETTER 'e'
#define ENTERANCE_LETTER 'E'
#define AIR_LETTER ' '
#define WALL_LETTER 'x'




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
    std::ofstream off;
    int mapChoice;
    bool over;
    int attackersLeft;
    int alHP;
    int alDMG;
    

    
    CMap(int mapChoice);
    CMap(){};
    void redraw(WINDOW * win);
    void loadMap(int & loadedX, int  & loadedY);
    void buy(int index, AttackerConf & a);
    void enteranceUp();
    void enteranceDown();
    void calculatePath( CAttacker * a, char lookingFor);
    void placeTowers(int n, std::vector<TowerConf> & a);
    void interact();
    void winScreen(WINDOW * win);
    void LoseScreen(WINDOW * win);
    
    
 
};


