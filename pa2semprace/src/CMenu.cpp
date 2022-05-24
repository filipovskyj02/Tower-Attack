#include "CMenu.hpp"


CMenu::CMenu(int p_width,int p_height){
    
    this->continueToGame = false;
    initscr();
    refresh();
    this->maxW = p_width * WIDTH_MULTI;
    this->maxH = p_height;
    std::vector<std::string> MenuChoices = {"Start","Help","Quit"};
    int WinMaxY,WinMaxX;
    
    getmaxyx(stdscr,WinMaxY,WinMaxX);

    WINDOW * boardWin = newwin(maxH,maxW,WinMaxY/SCREEN_POS,WinMaxX/SCREEN_POS);
    box(boardWin,0,0);
    refresh();
    wrefresh(boardWin);
    
    mvwprintw(boardWin,0,maxW/2.6,"Tower Attack");
    std::pair <int,int> MenuItems;
    keypad(boardWin,true);
    int choice = 0;
    unsigned int selected = 0;
    while (choice != 10) {
        
        MenuItems = {2,maxW/2.3 };

        for (unsigned int i = 0; i < MenuChoices.size(); i++){
            
            
            if (i == selected) wattron(boardWin,A_REVERSE);
            mvwprintw(boardWin,MenuItems.first,MenuItems.second,MenuChoices[i].c_str());
            wattroff(boardWin,A_REVERSE);
            
            MenuItems.first += MENU_ITEM_DISTANCE;
        }
        
        choice = wgetch(boardWin);
        if (choice == KEY_DOWN) selected = (selected + 1) % 3;
        else if (choice == KEY_UP) selected == 0 ? selected = 2 : selected--;
       

        

    }
    //for (int k = 0; k < 10; k++)std::cout << selected << "\n";
    if (selected == 1) help(boardWin);
    else if (selected == 0) continueToGame = true;
    
    getch();
    endwin();




}
 void CMenu::help (WINDOW * MenuWin){
     
     mvwprintw(MenuWin, maxH/2,maxW/2,"Test helpu");
     
     int tt;
     tt = wgetch(MenuWin);
     

 }
 bool CMenu::contin (){
     return this->continueToGame;
 }
