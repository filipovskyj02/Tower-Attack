#include "CGame.hpp"

CGame::CGame (int mapChoice, int confChoice){
    curs_set(0);
    noecho();
    if (!this->parseFile(confChoice)) return;
    int min = stoi(NameCost[0].second);
    for (auto i : NameCost){
        if (stoi(i.second) < min) min = stoi(i.second);
    }
    this->cheapest = min;
    this->waiting = false;
    this->mapChoice = mapChoice;
    isOver = false;
    
    
    getmaxyx(stdscr,ScreenY,ScreenX);
    clear();
    initscr();
    refresh();

    
    
    
    this->gameMap = CMap(mapChoice);
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
    
    int spaceForOne = this->row_width/NameCost.size();
    
    int enteranceChoice = 0;
    int choice = 0;
    unsigned int selected = 0;
    

    std::chrono::time_point<std::chrono::system_clock> t = std::chrono::system_clock::now();
    this->gameMap.placeTowers(towerAmount,tww);


    while (!this->gameMap.over) {
       
        
         t += std::chrono::milliseconds(80);
        std::this_thread::sleep_until(t);

        if(this->gameMap.TowerVec.empty() and ((!this->gameMap.DynamicVec.empty()) or (playerMoney>this->cheapest) )) this->gameMap.winScreen(mapBoundary);
        if(this->gameMap.DynamicVec.empty() and this->gameMap.TowerVec.size() and playerMoney < cheapest) this->gameMap.LoseScreen(mapBoundary);
        
        this->gameMap.redraw(mapBoundary);
        if (this->gameMap.alHP > minHealthToWin and this->gameMap.alDMG > minDmgToWin) this->gameMap.winScreen(mapBoundary);
        this->gameMap.interact();
        InfoRefresh(InfoBar);
       
        
        
        for (unsigned int i = 0; i < NameCost.size(); i++){
            
            int halfLen = NameCost[i].first.length()/2;
            int halfLenPrice = NameCost[i].first.length()/2; 
            if (i == selected) wattron(Menu,A_REVERSE);
            mvwprintw(Menu,(MENU_HEIGHT/3),(spaceForOne/2)-halfLen + (i*spaceForOne),NameCost[i].first.c_str());
            mvwprintw(Menu,(MENU_HEIGHT/3)*2 + 1,(spaceForOne/2)-halfLenPrice + (i*spaceForOne),NameCost[i].second.c_str());
            wattroff(Menu,A_REVERSE);
            
           
        }
        
        choice = wgetch(Menu);
        
        
        switch(choice){
            case KEY_UP: 
                this->gameMap.enteranceUp();
                break;
            case KEY_DOWN: 
                this->gameMap.enteranceDown();
                break;
            case KEY_RIGHT: 
                selected = (selected + 1) % NameCost.size();
                break;
            case KEY_LEFT: 
                selected == 0 ? selected = NameCost.size() - 1 : selected--;
                break;
            case 10: 
                if (playerMoney >= stoi(NameCost[selected].second)){
                this->gameMap.buy(selected,att[selected]);
                playerMoney -= stoi(NameCost[selected].second);
                }
                
                break;
            

        }
        //Escape pressed
        if (choice == 27){
            if (escOptions(mapBoundary)== false) break;
            t = std::chrono::system_clock::now();
            

        }
        
    }
    
    wclear(mapBoundary);
    wclear(InfoBar);
    wclear(Menu);
    wrefresh(mapBoundary);
    endwin();
    clear();
    

}

void CGame::InfoRefresh(WINDOW * InfoBar){
    wclear(InfoBar);
    box(InfoBar,0,0);
    mvwprintw(InfoBar,INFO_HEIGHT/4,this->row_width/7 ,"Alive: ");
    wprintw(InfoBar,std::to_string(this->gameMap.DynamicVec.size()).c_str());
    mvwprintw(InfoBar,INFO_HEIGHT/4,(this->row_width/7) * 5 ,"Money: ");
    wprintw(InfoBar,std::to_string(playerMoney).c_str());
    mvwprintw(InfoBar,INFO_HEIGHT/2,this->row_width/2 - 4,"Exited: ");
    wprintw(InfoBar,std::to_string(this->gameMap.attackersLeft).c_str());
    std::string line1 = {"Dmg : " + std::to_string(this->gameMap.alDMG) + " / " + std::to_string(this->minDmgToWin) +'\n'};
    std::string line2 = {"Hp : " + std::to_string(this->gameMap.alHP) + " / " + std::to_string(this->minHealthToWin)};
    mvwprintw(InfoBar,((INFO_HEIGHT/6) *6) - 1,(this->row_width/2 - line1.size()/2),line1.c_str());
    mvwprintw(InfoBar,((INFO_HEIGHT/6) * 6) ,(this->row_width/2 - line2.size()/2),line2.c_str());
    wrefresh(InfoBar);
}

bool CGame::escOptions(WINDOW * win){
    this->waiting = true;
    wclear(win);
    wrefresh(win);
    box(win,0,0);
    
    std::vector<std::string> MenuChoices = {"Continue","Save Game","Exit"};
    keypad(win,true);
    int choice = 0;
    unsigned int selected = 0;
    int spaceForOne = collum_height/MenuChoices.size();
    while (choice != 10){
    for (unsigned int i = 0; i < MenuChoices.size(); i++){
            
            int halfLen = MenuChoices[i].length()/2;

            if (i == selected) wattron(win,A_REVERSE);
            mvwprintw(win,(collum_height/spaceForOne) * (i+1),row_width/2 - 5,MenuChoices[i].c_str());
            
            wattroff(win,A_REVERSE);
            
           
        }
        
    choice = wgetch(win);
    switch (choice){
         case KEY_DOWN: 
                selected = (selected + 1) % MenuChoices.size();
                break;
            case KEY_UP: 
                selected == 0 ? selected = MenuChoices.size()-1 : selected--;
                break;
            case 10: 
                if (selected == 0)return true;
                else if (selected == 1)return true; 
                else if (selected == 2) return false;
                

    }

    }
        

 }
    


