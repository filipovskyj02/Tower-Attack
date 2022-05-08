#pragma once
#include <iostream>
#include <string>
#include "CGame.hpp"
class CMenu
{
private:
    
public:
    bool continueToGame;
    std::string userInput;

    CMenu(/* args */);
    ~CMenu();
    
    void help();
    void start();

    
};


