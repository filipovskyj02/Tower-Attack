#pragma once
#include "ncurses.h"
#include "vector"
#include "CTower.hpp"

class CTower;

class CAttacker{
    public:
    /**
     * @brief letter to show
     * 
     */
    char C;
    CAttacker(char C);
    CAttacker();
    /**
     * @brief current x coordinate
     * 
     */
    int x;
    /**
     * @brief current y coordinate
     * 
     */
    int y;
    /**
     * @brief amount of damage dealt to enemies when in range
     * 
     */
    int damage;
    /**
     * @brief how often the attacker moves. Higher = slower
     * 
     */
    int runSpeed;
    /**
     * @brief exact X Y of every step that needs to be taken to reach destination
     * 
     */
    std::vector<std::pair<int,int>> path;
    /**
     * @brief current position on the path above
     * 
     */
    int pathIndex;
    /**
     * @brief  the attacker left the map by reaching exit
     * 
     */
    bool left;
    /**
     * @brief variable that increases by one every update 
     * resets back to 0 when runSpeed is reached and moves the character
     * 
     */
    int moveCnt;
    /**
     * @brief current health
     * 
     */
    int health;
    /**
     * @brief max health
     * 
     */
    int fullHealth;
    /**
     * @brief the diameter of a cirle. The attacker can deal damage to every tower inside this circle
     * 
     */
    int range;
    /**
     * @brief how often the attacker can shoot bigger = slower
     * 
     */
    int fireFrequency;
    /**
     * @brief variable that increases by one every update 
     * resets back to 0 when fireFrequency is reached and moves the character
     * 
     */
    int shotsCnt;
    /**
     * @brief what to save to a save file 
     * 
     */
    int attackerIndex;
    /**
     * @brief stores if the attacker is dead and should be removed next update
     * 
     */
    bool dead;
    
    
     /**
      * @brief CMap calls this method for each attacker and lets him draw himself on the map
      * 
      * @param map where to draw itself
      */
    virtual void draw(WINDOW * map) = 0;
    /**
     * @brief CMap calls this every game update, defines what to do and how to move
     * 
     */
    virtual void move(void) = 0;
    /**
     * @brief defines what to do when a Tower is in range, takes health direcly from it if not reloading
     * 
     * @param enemy 
     */
    virtual void attack(CTower * enemy) = 0;
    /**
     * @brief returns what is the attacker looking for when pathfinding, towers/exits
     * 
     * @return char the character that the attacker is looking for
     */
    virtual char whatToFind() = 0;

};