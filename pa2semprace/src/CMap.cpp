#pragma once
#include "CMap.hpp"


CMap::CMap (){
    curs_set(0);
    
    this->enteranceSel = 0;
    
}



void CMap::buy (int index){
   
    switch (index){
        case 0: DynamicVec.push_back(std::make_unique<CHogRider>(EnteranceCords[this->enteranceSel]%this->sizeX,EnteranceCords[this->enteranceSel] / this->sizeX));
            break;
        case 1: DynamicVec.push_back(std::make_unique<CTank>(EnteranceCords[this->enteranceSel]%this->sizeX,EnteranceCords[this->enteranceSel] / this->sizeX));
            break;
    }
    
    calculatePath(DynamicVec.back().get(),'l');
    

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
void CMap::towerFire(){
    for (unsigned int i = 0; i < TowerVec.size(); i++){
        for (unsigned int j = 0; j < DynamicVec.size(); j++){
            int distanceX = DynamicVec[j].get()->x - TowerVec[i].get()->x;
            int distanceY = DynamicVec[j].get()->y - TowerVec[i].get()->y;
            if ((distanceX < TowerVec[i].get()->range/2) and (distanceX > ((TowerVec[i].get()->range/2)*-1)))
                if ((distanceY < TowerVec[i].get()->range/2) and (distanceY > ((TowerVec[i].get()->range/2)*-1)))
                    DynamicVec[j].get()->health -=  TowerVec[i].get()->damage;
        }



    }
    



}



