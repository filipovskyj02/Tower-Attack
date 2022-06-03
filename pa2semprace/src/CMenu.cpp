#include "CMenu.hpp"

CMenu::CMenu(){
    this->exit = false;
    
}
void CMenu::draw(int p_width,int p_height){
    
    

    
    this->exit = false;
    this->continueToGame = false;
    initscr();
    refresh();
    this->maxW = p_width * WIDTH_MULTI;
    this->maxH = p_height;
    std::vector<std::string> MenuChoices = {"New  Game","Load Game","Help","Quit"};
    int WinMaxY,WinMaxX;
    
    getmaxyx(stdscr,WinMaxY,WinMaxX);

    WINDOW * boardWin = newwin(maxH,maxW,(WinMaxY/2)-maxH/2,(WinMaxX/2)-maxW/2);
    curs_set(0);
    box(boardWin,0,0);
    refresh();
    wrefresh(boardWin);
    
    mvwprintw(boardWin,0,maxW/2 - 6,"Tower Attack");
    std::pair <int,int> MenuItems;
    keypad(boardWin,true);
    int choice = 0;
    unsigned int selected = 0;
    while (choice != 10) {
        
        MenuItems = {maxH/4,(maxW/2) - 2 };

        for (unsigned int i = 0; i < MenuChoices.size(); i++){
            
            
            if (i == selected) wattron(boardWin,A_REVERSE);
            mvwprintw(boardWin,MenuItems.first,(maxW/2) - (MenuChoices[i].size()/2),MenuChoices[i].c_str());
            wattroff(boardWin,A_REVERSE);
            
            MenuItems.first += 2;
        }
        
        choice = wgetch(boardWin);
        if (choice == KEY_DOWN) selected = (selected + 1) % 4;
        else if (choice == KEY_UP) selected == 0 ? selected = 3 : selected--;
       

        

    }
    
    if (selected == 1) help(boardWin);
    else if (selected == 0) NewGame(boardWin);
    else exit++;

    
    
    endwin();




}
 void CMenu::help (WINDOW * MenuWin){
     
     mvwprintw(MenuWin, maxH/2,maxW/2,"Test helpu");
     
     


     

 }
 bool CMenu::contin (){
     return this->continueToGame;
 }
 void CMenu::NewGame(WINDOW * MenuWin){
    wclear(MenuWin);
    wrefresh(MenuWin);
    box(MenuWin,0,0);
    mvwprintw(MenuWin,0,maxW/2 - 6,"Choose a map");
    std::vector<std::string> MenuChoices = {"Map 1","Map 2","Map 3","Maze 1", "Maze 2"};
    keypad(MenuWin,true);
    int choice = 0;
    unsigned int selected = 0;
    int spaceForOne = maxH/MenuChoices.size();
    while (choice != 10){
    for (unsigned int i = 0; i < MenuChoices.size(); i++){
            
            int halfLen = MenuChoices[i].length()/2;

            if (i == selected) wattron(MenuWin,A_REVERSE);
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
                continueToGame++;
                this->mapChoice = selected;
                break;



    }

    }
        
    


 }
