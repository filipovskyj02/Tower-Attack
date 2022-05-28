#include "CGame.hpp"

CGame::CGame (int collum_height, int row_width){
    curs_set(0);
    

    isOver = false;
    playerMoney = 20000;
    
    getmaxyx(stdscr,ScreenY,ScreenX);
    clear();
    initscr();
    refresh();

    start_color();
    //init_pair(1,COLOR_BLUE, COLOR_RED);
   //wbkgd(Menu, COLOR_PAIR(1));
    
    
    this->gameMap = CMap();
    this->gameMap.loadMap(this->row_width,this->collum_height);
   
    WINDOW * mapBoundary = newwin(this->collum_height,this->row_width,(ScreenY/2)-this->collum_height/2,(ScreenX/2)-this->row_width/2);
    WINDOW * Menu = newwin(MENU_HEIGHT,this->row_width,(ScreenY/2)+this->collum_height/2,(ScreenX/2)-this->row_width/2);
    WINDOW * InfoBar = newwin(INFO_HEIGHT,this->row_width,(ScreenY/2)-this->collum_height/2-INFO_HEIGHT,(ScreenX/2)-this->row_width/2);
    refresh();
    box(mapBoundary,0,0);
    box(Menu,0,0);
    wrefresh(Menu);
    wrefresh(InfoBar);
    
    wrefresh(mapBoundary);
    keypad(Menu,true);
    nodelay(Menu, true);
   
    InfoRefresh(InfoBar);
    
    std::vector<std::string> eneme = {"Hog Rider","Wizard","Frog","Pig"};
    std::vector<std::string> cost = {"100","500","300","10"};
    int spaceForOne = this->row_width/eneme.size();
    
    int enteranceChoice = 0;
    int choice = 0;
    unsigned int selected = 0;
    

     std::chrono::time_point<std::chrono::system_clock> t = std::chrono::system_clock::now();
      this->gameMap.placeTowers(10);


    while (true) {
       
         t += std::chrono::milliseconds(80);
        std::this_thread::sleep_until(t);

        
        this->gameMap.redraw(mapBoundary);
        InfoRefresh(InfoBar);
       
        
        
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
            this->gameMap.buy(selected);
            playerMoney -= stoi(cost[selected]);
            

        }
        else if (choice == KEY_UP) {this->gameMap.enteranceUp();this->gameMap.redraw(mapBoundary);}
        else if (choice == KEY_DOWN) {this->gameMap.enteranceDown();this->gameMap.redraw(mapBoundary);}
        
    }
        

     
        
    int l = wgetch(mapBoundary); 
    endwin();
    clear();
    

}

void CGame::InfoRefresh(WINDOW * InfoBar){
    wclear(InfoBar);
    box(InfoBar,0,0);
    mvwprintw(InfoBar,(MENU_HEIGHT/2),this->row_width/5 ,"Soldiers Alive: ");
    wprintw(InfoBar,std::to_string(this->gameMap.DynamicVec.size()).c_str());
    mvwprintw(InfoBar,(MENU_HEIGHT/2),(this->row_width/3) * 2 ,"Money: ");
    wprintw(InfoBar,std::to_string(playerMoney).c_str());
    wrefresh(InfoBar);
}

