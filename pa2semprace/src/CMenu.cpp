#pragma once
#include <iostream>
#include <string>
#include "CGame.hpp"
class CMenu
{
private:
    
public:
    bool continueToGame = false;
    std::string userInput;
    CMenu(/* args */);
    ~CMenu();
    
    void help(void){
        std::cout << "type new to start a new game\n";
        std::cout << "type commands to show all commans\n";
        std::cout << "type quit to quit the game\n";


    }
    void start(){
        while (true){

            std::cin >> userInput;
            if (userInput == "new") continueToGame = true;
            else if (userInput == "help") help();
            else if (userInput == "quit") break;
            else {std::cout << "Incorrect input\n";}

        }


    }

    
};


