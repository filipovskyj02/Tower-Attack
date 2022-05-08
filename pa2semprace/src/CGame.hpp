#pragma once
#include "vector"
class CGame
{
public:
    
    CMap gameMap;
    int playerMoney;
    
    bool LoadGame();
    void newGame();
    void initalize();
    void gameLoop();
    void buyAttackers();
    



};


