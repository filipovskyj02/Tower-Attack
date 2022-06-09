#pragma once

#include "vector"
#include "ncurses.h"
#include "iostream"
#include <fstream>
#include "CCell.hpp"
#include "memory"
#include "CCellBasic.hpp"
#include "CAttacker.hpp"
//#include "CTower.hpp"
#include "CHogRider.hpp"
#include "CLaserTurret.hpp"
#include "CMapScout.hpp"
#include "CTank.hpp"
#include "CTower2.hpp"
#include "CJumper.hpp"
#include "CLongRange.hpp"
#include "algorithm"

#define TOWER_LETTER 'T'
#define EXIT_LETTER 'e'
#define ENTERANCE_LETTER 'E'
#define AIR_LETTER ' '
#define WALL_LETTER 'x'


class CMap
{
    public:
    /**
     * @brief width of the map, calculated when reading map.txt file
     * 
     */
    int sizeX;
    /**
     * @brief height of the map, calculated when reading map.txt file
     * 
     */
    int sizeY;
    
    /**
     * @brief vector of unique pointers to CCell class, CCell represensnts static objects
     * 
     */
    std::vector<std::unique_ptr<CCell>> mapVec;
    /**
     * @brief vector of unique pointers to CAttacker class, CAttacker is dynamic
     * 
     */
    std::vector<std::unique_ptr<CAttacker>> DynamicVec;
    /**
     * @brief vector of unique pointers to CTower class, CTower is dynamic
     * 
     */
    std::vector<std::unique_ptr<CTower>> TowerVec;
    /**
     * @brief stores cooardinates of enterances that were calculated when map loading
     * 
     */
    std::vector<unsigned int> EnteranceCords;
    /**
     * @brief stores cooardinates of exits that were calculated when map loading
     * 
     * 
     */
    std::vector<unsigned int> ExitCords;
    /**
     * @brief stores which exit the player has currently as selected/highlited
     * 
     */
    int enteranceSel;
    /**
     * @brief the amount of enterances read from the coresponding map.txt file
     * 
     */
    int enteranceCnt;
    /**
     * @brief stream to a file for debugging purposes
     * 
     */
   
    int mapChoice;
    /**
     * @brief is the game over yet
     * 
     */
    bool over;
    /**
     * @brief stores how many attackers has succesfuly crossed the map
     * 
     */
    int attackersLeft;
    /**
     * @brief combined total of hp of attackers left
     * 
     */
    int alHP;
    /**
     * @brief combined total of dmg of attackers left
     * 
     */
    int alDMG;
    
    

    
    CMap(int mapChoice);
    CMap(){};
    /**
     * @brief redraws the map completely, including both static and dynamic entities
     * 
     * @param win 
     */
    void redraw(WINDOW * win);
    /**
     * @brief loads a map.txt file based on player choosing
     * 
     * @param loadedX width of the loaded map
     * @param loadedY height of the loaded map
     */
    void loadMap(int & loadedX, int  & loadedY);
    /**
     * @brief called when player hits enter, buys the currently highlited attacker
     * 
     * @param index currently highlited attacker
     * @param a loaded conf stats of the attacker
     */
    void buy(int index, AttackerConf & a);
    /**
     * @brief  called when player hits up, moves the highlited enterance to spawn attackers at up
     * 
     */
    void enteranceUp();
    /**
     * @brief called when player hits up, moves the highlited enterance to spawn attackers at down
     * 
     */
    void enteranceDown();
    /**
     * @brief method that calculates path for the attacker to take, uses bfs, stores the path into vector of the attacker
     * 
     * @param a the attacker to calculate for
     * @param lookingFor what is the attacker looking to path toward. T = tower, e = exit...
     */
    void calculatePath( CAttacker * a, char lookingFor);
    /**
     * @brief tower placing ai
     * 
     * @param n how many towers to place
     * @param a tower configurations
     */
    void placeTowers(int n, std::vector<TowerConf> & a);
    /**
     * @brief calculates range intersections of towers and attackers, calls interaction methods of the attackers/towers
     * 
     */
    void interact();
    /**
     * @brief shows the U won text
     * 
     * @param win window to show it at
     */
    void winScreen(WINDOW * win);
    /**
     * @brief shows the U lost text
     * 
     * @param win window to show it at
     */
    void LoseScreen(WINDOW * win);
    
    
 
};


