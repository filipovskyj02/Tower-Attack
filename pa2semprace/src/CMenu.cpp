#include "CMenu.hpp"

CMenu::CMenu(){
    this->exit = false;
    
}
void CMenu::draw(int p_width,int p_height){
    
    
    this->loadedFile = -1;
    this->confChoice = 0;
    this->exit = false;
    this->continueToGame = false;
    initscr();
    refresh();
    this->maxW = p_width * WIDTH_MULTI;
    this->maxH = p_height;
    int WinMaxY,WinMaxX;
    
    getmaxyx(stdscr,WinMaxY,WinMaxX);

    WINDOW * boardWin = newwin(maxH,maxW,(WinMaxY/2)-maxH/2,(WinMaxX/2)-maxW/2);
    std::vector<std::string> menuText = {"New  Game","Load Game","Help","Quit"};
    std::string text = {"Tower Attack !"};
    int selection = 0;
    DrawMenu(boardWin,menuText,text,selection);
    
    
    int selection2 = 0;
    switch (selection){
        case 0:
            menuText = {"Map 1","Map 2","Map 3","Maze 1", "Maze 2"};
            text = {"Choose a map !"};
            DrawMenu(boardWin,menuText,text,selection2);
            this->mapChoice = selection2;
            menuText = {"Hard","Medium","Easy","Free"};
            text = {"Choose a configuration file !"};
            DrawMenu(boardWin,menuText,text,selection2);
            this->confChoice = selection2;
            continueToGame = true;
            break;
        case 1:
            menuText = {"Save Slot 1","Save Slot 2","Save Slot 3", "Save Slot 4", "Save Slot 5"};
            text = {"Select a file to load"};
            DrawMenu(boardWin,menuText,text,selection2);
            this->loadedFile = selection2;
            continueToGame = true;
            break;

        case 2: 
            help(boardWin);
            break;
        default:
            exit = true;
            break;

    }
     
    endwin();

}
 void CMenu::help (WINDOW * MenuWin){
     
    mvwprintw(MenuWin, maxH/2,maxW/2,"Test helpu");
     


 }
 bool CMenu::contin (){
     return this->continueToGame;
 }
 void CMenu::DrawMenu(WINDOW * MenuWin, std::vector<std::string> & MenuChoices,std::string & Text, int & selected){
    curs_set(0);
    noecho();
    wclear(MenuWin);
    wrefresh(MenuWin);
    box(MenuWin,0,0);
    mvwprintw(MenuWin,0,maxW/2 - Text.length()/2,Text.c_str());
    
    keypad(MenuWin,true);
    int choice = 0;
    int spaceForOne = maxH/MenuChoices.size();
    while (choice != 10){
        for (unsigned int i = 0; i < MenuChoices.size(); i++){

                int halfLen = MenuChoices[i].length()/2;

                if (i == (unsigned)selected) wattron(MenuWin,A_REVERSE);
                mvwprintw(MenuWin,(spaceForOne)-halfLen + (i*spaceForOne),maxW/2-MenuChoices[i].size()/2,MenuChoices[i].c_str());

                wattroff(MenuWin,A_REVERSE);


            }

        choice = wgetch(MenuWin);
        switch (choice){
             case KEY_DOWN: 
                    selected = (selected + 1) % MenuChoices.size();
                    break;
            case KEY_UP: 
                    selected == 0 ? selected = MenuChoices.size()-1 : selected--;
                    break;
            case 10: 
                    break;

        }

    }
        
 }
