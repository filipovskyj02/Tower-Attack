#pragma once
#include "CMap.hpp"


CMap::CMap (int mapChoice){
    curs_set(0);
    off.open("out.txt");
    this->enteranceSel = 0;
    this->mapChoice = mapChoice;
    this->over = false;
    this->attackersLeft = 0;
    this->alDMG = 0;
    this->alHP = 0;
    
}
void CMap::LoseScreen(WINDOW * win){
    wclear(win);
    wrefresh(win);
    box(win,0,0);
    mvwprintw(win,sizeY/2,sizeX/2 - 4,"You Lose !");
    this->over++;
    wgetch(win);


}
void CMap::winScreen(WINDOW * win){
    wclear(win);
    wrefresh(win);
    box(win,0,0);
    mvwprintw(win,sizeY/2,sizeX/2 - 4,"You Win !");
    this->over++;
    wgetch(win);

}



void CMap::buy (int index, AttackerConf & a){
   
    switch (index){
        case 0: DynamicVec.push_back(std::make_unique<CHogRider>(EnteranceCords[this->enteranceSel]%this->sizeX,EnteranceCords[this->enteranceSel] / this->sizeX, a));
            break;
        case 1: DynamicVec.push_back(std::make_unique<CTank>(EnteranceCords[this->enteranceSel]%this->sizeX,EnteranceCords[this->enteranceSel] / this->sizeX, a));
            break;
    }
    
    this->calculatePath(DynamicVec.back().get(),DynamicVec.back().get()->whatToFind());
    if (DynamicVec.back().get()->path.empty())  this->calculatePath(DynamicVec.back().get(),TOWER_LETTER);
    

}
void CMap::enteranceDown(){
    mapVec[EnteranceCords[this->enteranceSel]-1].get()->C='n';
    this->enteranceSel = (this->enteranceSel + 1) % enteranceCnt;
    mapVec[EnteranceCords[this->enteranceSel]-1].get()->C='s';
    

}
void CMap::enteranceUp(){
    mapVec[EnteranceCords[this->enteranceSel]-1].get()->C='n';
    this->enteranceSel == 0 ? this->enteranceSel = enteranceCnt-1 : this->enteranceSel--;
    mapVec[EnteranceCords[this->enteranceSel]-1].get()->C='s';
    

}
void CMap::interact(){
    

    for (unsigned int i = 0; i < TowerVec.size(); i++){
        for (unsigned int j = 0; j < DynamicVec.size(); j++){
            int attackerRange = DynamicVec[j].get()->range/2;
            int towerRange = TowerVec[i].get()->range/2;

            int distanceX = TowerVec[i].get()->x - DynamicVec[j].get()->x;
            int distanceY = TowerVec[i].get()->y - DynamicVec[j].get()->y;
            if (((distanceX < towerRange) and (distanceX > (towerRange*-1))) and ((distanceY < towerRange) and (distanceY > (towerRange*(-1))))){
                
                TowerVec[i].get()->attack(DynamicVec[j].get());
                off << DynamicVec[j].get()->health << std::endl;
                
                }
            if (((distanceX < attackerRange) and (distanceX > (attackerRange*-1))) and ((distanceY < attackerRange) and (distanceY > (attackerRange*(-1))))){
                DynamicVec[j].get()->attack(TowerVec[i].get());
                if (TowerVec[i].get()->health <= 0) {
                    bool noExitRoute = false;
                    TowerVec[i].get()->C = AIR_LETTER;
                    mapVec[TowerVec[i].get()->x + (TowerVec[i].get()->y*sizeX)].get()->C = AIR_LETTER;
                    TowerVec[i].get()->destroyed++;
                    std::unique_ptr<CMapScout> ptr = std::make_unique<CMapScout>(EnteranceCords[0]%sizeX,EnteranceCords[0]%sizeX);
                    calculatePath(ptr.get(),ptr.get()->whatToFind());
                    if ( ptr.get()->path.size() < 1) noExitRoute = true;
                    for (unsigned int p = 0; p < DynamicVec.size(); p++){
                        if (1/*DynamicVec[p].get()->path.back().first < sizeX - 1*/){
                            if (noExitRoute) calculatePath(DynamicVec[p].get(),TOWER_LETTER);
                            else calculatePath(DynamicVec[p].get(),DynamicVec[p].get()->whatToFind());
                        } 
                    }
                }
                        
                    
            }
        }
    }   



    }






