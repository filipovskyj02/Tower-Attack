#pragma once
#include "vector"
#include "ncurses.h"
#include "iostream"
#include "CMap.hpp"
#include "chrono"
#include "thread"
#include "sstream"
#include "string"
#include "SConf.hpp"
#include "CTower2.hpp"

#define MENU_ITEM_DISTANCE 2

#define MENU_HEIGHT 5
#define INFO_HEIGHT 8




class CGame
{
    /**
     * @brief loaded width of the game map loaded from a map.txt file
     * 
     */
    int row_width;
    /**
     * @brief loaded width of the game map loaded from a map.txt file
     * 
     */
    int collum_height;
    /**
     * @brief self explanatory
     * 
     */
    bool isOver;
    /**
     * @brief stores the map class of the respective game
     * 
     */
    CMap gameMap;
    /**
     * @brief loaded from a save file
     * 
     */
    int playerMoney;
    /**
     * @brief how many tower are on the map at the start of the game. Tower placing ai places this many towers
     *  
     * 
     */
    int towerAmount;
    /**
     * @brief width of the user console !not any of the 3 windows
     * 
     */
    int ScreenX;
     /**
     * @brief height of the user console !not any of the 3 windows
     * 
     */
    int ScreenY;
    /**
     * @brief which map the user selected
     * 
     */
    int mapChoice;
    /**
     * @brief stores the cheapest attacker, uses this value for win/lose conditions
     * 
     */
    int cheapest;
    /**
     * @brief loaded from conf file, if the combined health and dmg of attackers that have left the map without dying surpasses
     * this value, the player wins
     * 
     */
    int minHealthToWin;
    /**
     * @brief loaded from conf file, if the combined health and dmg of attackers that have left the map without dying surpasses
     * this value, the player wins
     * 
     */
    int minDmgToWin;
    /**
     * @brief which conf file the player choosed to load from
     * 
     */
    int confChoice;
    /**
     * @brief which save file the player choosed to save into
     * 
     */
    int saveChoice;

   


public:

    CGame();
    CGame(int mapChoice, int confChoice, int loadChoice);
    /**
     * @brief refreshes and redraws the info bar 
     * 
     * @param InfoBar pointer to infobar to redraw
     */
    void InfoRefresh(WINDOW * InfoBar);
 
    void Options(WINDOW * MenuWin, std::vector<std::string> & MenuChoices,std::string & Text, int & selected);
    /**
     * @brief Parses a configuration file and loads the values into att and tww vector
     * 
     * @param confChoice which conf File the user selected
     * @return true when parsing is succesful
     * @return false when parsing fails
     */
    bool parseFile(int confChoice);
    /**
     * @brief saves map choice, conf file choice and all dynamic objects into a file selected in the previous step
     * 
     */
    void saveGame();
    /**
     * @brief alternative to new game, creates a new map and loads conf file, then places all dynamic entities loaded from a file into their respective vectors 
     * 
     * @param loadChoice which save slot (1-5) the user selected
     */
    void loadSave(int loadChoice);
    /**
     * @brief stores pairs of the attacker name and its cost to buy 
     * 
     */
    std::vector<std::pair<std::string,std::string>> NameCost;
    /**
     * @brief stores attacker configurations loaded from a file
     * 
     */
    std::vector<AttackerConf> att;
      /**
     * @brief stores tower configurations loaded from a file
     * 
     */
    std::vector<TowerConf> tww;

};


