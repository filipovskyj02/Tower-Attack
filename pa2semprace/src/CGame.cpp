#include "CGame.hpp"

CGame::CGame (int collum_height, int row_width){
    isOver = false;
    playerMoney = 20000;
    this->collum_height = collum_height;
    this->row_width = row_width * WIDTH_MULTI;
    getmaxyx(stdscr,ScreenY,ScreenX);
    clear();
    initscr();
    refresh();
    WINDOW * mapBoundary = newwin(this->collum_height,this->row_width,ScreenY/SCREEN_POS,ScreenY/SCREEN_POS);
    WINDOW * Menu = newwin(MENU_HEIGHT,this->row_width,(ScreenY/SCREEN_POS)+this->collum_height,ScreenY/SCREEN_POS);
    WINDOW * InfoBar = newwin(INFO_HEIGHT,this->row_width,(ScreenY/SCREEN_POS)-INFO_HEIGHT,ScreenY/SCREEN_POS);
    start_color();
    //init_pair(1,COLOR_BLUE, COLOR_RED);
   //wbkgd(Menu, COLOR_PAIR(1));
    box(mapBoundary,0,0);
    box(Menu,0,0);
    
    wrefresh(Menu);
    wrefresh(InfoBar);
    
    wrefresh(mapBoundary);
    keypad(Menu,true);
   
    InfoRefresh(InfoBar);

    std::vector<std::string> eneme = {"Hog Rider","Wizard","Frog","Pig"};
    std::vector<std::string> cost = {"100","500","300","10"};
    int spaceForOne = this->row_width/eneme.size();
   
    int choice = 0;
    unsigned int selected = 0;

   

    while (true) {
        
        for (unsigned int i = 0; i < eneme.size(); i++){
            
            int halfLen = eneme[i].length()/2;
            int halfLenPrice = cost[i].length()/2; 
            if (i == selected) wattron(Menu,A_REVERSE);
            mvwprintw(Menu,(MENU_HEIGHT/3),(spaceForOne/2)-halfLen + (i*spaceForOne),eneme[i].c_str());
            mvwprintw(Menu,(MENU_HEIGHT/3)*2 + 1,(spaceForOne/2)-halfLenPrice + (i*spaceForOne),cost[i].c_str());
            wattroff(Menu,A_REVERSE);
            
           
        }
        
        choice = wgetch(Menu);
        if (choice == KEY_RIGHT) selected = (selected + 1) % eneme.size();
        else if (choice == KEY_LEFT) selected == 0 ? selected = eneme.size()-1 : selected--;
        else if (choice == 10){
            playerMoney -= stoi(cost[selected]);
            InfoRefresh(InfoBar);

        }
    }
        

     
        
    int l = wgetch(mapBoundary); 
    endwin();
    clear();
    

}

void CGame::InfoRefresh(WINDOW * InfoBar){
    wclear(InfoBar);
    box(InfoBar,0,0);
    mvwprintw(InfoBar,(MENU_HEIGHT/2),this->row_width/5 ,"Soldiers Alive: ");
    wprintw(InfoBar,"10");
    mvwprintw(InfoBar,(MENU_HEIGHT/2),(this->row_width/3) * 2 ,"Money: ");
    wprintw(InfoBar,std::to_string(playerMoney).c_str());
    wrefresh(InfoBar);
}