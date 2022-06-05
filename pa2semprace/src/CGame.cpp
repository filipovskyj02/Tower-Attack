#include "CGame.hpp"

CGame::CGame (int mapChoice, int confChoice, int loadChoice){
    curs_set(0);
    noecho();
    
    if (loadChoice >= 0) loadSave(loadChoice);
    else {
        this->mapChoice = mapChoice;
        this->confChoice = confChoice;
        if (!this->parseFile(confChoice)) return;
        this->gameMap = CMap(mapChoice);
        this->gameMap.loadMap(this->row_width,this->collum_height);
        this->gameMap.placeTowers(towerAmount,tww);
    }
    
    int min = stoi(NameCost[0].second);
    for (auto i : NameCost){
        if (stoi(i.second) < min) min = stoi(i.second);
    }
    this->cheapest = min;
    
   
    isOver = false;
    
    
    getmaxyx(stdscr,ScreenY,ScreenX);
    clear();
    initscr();
    refresh();

    
    
    
   
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
            int selected1 = 1;
            while (selected1 == 1){
            std::vector<std::string> menuText = {"Continue","Save Game","Quit"};
            std::string text = {"Menu"};
            Options(mapBoundary,menuText,text,selected1);
            if (selected1 == 0) t = std::chrono::system_clock::now();
            else if (selected1 == 1){
                
                std::vector<std::string> menuText1 = {"Save Slot 1","Save Slot 2","Save Slot 3", "Save Slot 4", "Save Slot 5"};
                text = {"Choose save location"};
                Options(mapBoundary,menuText1,text,selected1);
                this->saveChoice = selected1;
                saveGame();
                t = std::chrono::system_clock::now();
                selected1 = 1;
                

            }
        }
        if (selected1 == 2) break;
        
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

void CGame::Options(WINDOW * MenuWin, std::vector<std::string> & MenuChoices,std::string & Text, int & selected){
    curs_set(0);
    noecho();
    wclear(MenuWin);
    wrefresh(MenuWin);
    box(MenuWin,0,0);
    mvwprintw(MenuWin,0,row_width/2 - Text.length()/2,Text.c_str());
    
    keypad(MenuWin,true);
    int choice = 0;
    int shift = 1;
    if (MenuChoices.size() == 3) shift = 3;
    int spaceForOne = collum_height/MenuChoices.size();
    while (choice != 10){
        for (unsigned int i = 0; i < MenuChoices.size(); i++){

                int halfLen = MenuChoices[i].length()/2;

                if (i == selected) wattron(MenuWin,A_REVERSE);
                mvwprintw(MenuWin,(spaceForOne) - shift + (i*spaceForOne),row_width/2-MenuChoices[i].size()/2,MenuChoices[i].c_str());

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
                    return;

        }

    }
        
}
    


