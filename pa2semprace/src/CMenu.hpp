#pragma once
#include "ncurses.h"
#include "string"
#include "vector"
#include "iostream"
#include <filesystem>
#include <dirent.h>



#define WIDTH_MULTI 2.5



class CMenu
{
    
private:
    int maxW,maxH;
    bool continueToGame;
    
public:
    CMenu();
    void draw(int p_width,int p_height);
    void help (WINDOW * MenuWin);
    bool contin();
    bool exit;
    void DrawMenu(WINDOW * MenuWin, std::vector<std::string> & MenuChoices,std::string & Text, int & selected);
    int mapChoice;
    int confChoice;
    int loadedFile;
    
    
    
};

