#pragma once
#include "CMap.hpp"


CMap::CMap (){
    curs_set(0);
    off.open("out.txt");
    this->enteranceSel = 0;
    
}



void CMap::buy (int index){
   
    switch (index){
        case 0: DynamicVec.push_back(std::make_unique<CHogRider>(EnteranceCords[this->enteranceSel]%this->sizeX,EnteranceCords[this->enteranceSel] / this->sizeX));
            break;
        case 1: DynamicVec.push_back(std::make_unique<CTank>(EnteranceCords[this->enteranceSel]%this->sizeX,EnteranceCords[this->enteranceSel] / this->sizeX));
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
                
                }
            if (((distanceX < attackerRange) and (distanceX > (attackerRange*-1))) and ((distanceY < attackerRange) and (distanceY > (attackerRange*(-1))))){
                DynamicVec[j].get()->attack(TowerVec[i].get());
                if (TowerVec[i].get()->health <= 0) {
                    TowerVec[i].get()->C = AIR_LETTER;
                    mapVec[TowerVec[i].get()->x + (TowerVec[i].get()->y*sizeX)].get()->C = AIR_LETTER;
                    TowerVec[i].get()->destroyed++;
                    for (unsigned int p = 0; p < DynamicVec.size(); p++){
                        if (DynamicVec[p].get()->whatToFind() == TOWER_LETTER)
                        calculatePath(DynamicVec[p].get(),DynamicVec[p].get()->whatToFind());
                    }
                    }
                        
                    
                    }
                }
        }   



    }






