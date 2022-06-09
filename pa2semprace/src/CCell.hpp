#pragma once
#include "ncurses.h"
#include "utility"




class CCell{
    public:
    /**
     * @brief what the cell is, basically diferentiates between types, ! does not effect how the cell looks drawn to map
     * 
     */
    char C;
    CCell(char C, int total, int x, int y);
    CCell();
    /**
     * @brief is called every update, defines how the cell should draw itself to the game map
     * 
     * @param map where to draw self
     */
    virtual void draw(WINDOW * map) = 0;
    int xCord;
    int yCord;
    /**
     * @brief index of path
     * 
     */
    int Index;
    /**
     * @brief stores the index of the tower that could be placed onto the cell. Improves redrawing efficency. Prevent O(n)search of
     * the tower in its vector
     * 
     */
    int towerIndex;
    /**
     * @brief stores the index of the attacker that could be placed onto the cell. Improves redrawing efficency. Prevent O(n)search of
     * the attacker in its vector
     * 
     */
    int AttackerIndex;
    /**
     * @brief 0-9 represantation of health of the dynamic object that could be standing on the cell
     * 
     */
    int healthDraw;
    /**
     * @brief its coordinates in case the cell is traversed during pathfinding
     * 
     */
    
    std::pair<int,int> pathIndex;

};