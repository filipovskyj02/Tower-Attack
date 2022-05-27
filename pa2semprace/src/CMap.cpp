#pragma once
#include "CMap.hpp"


CMap::CMap (int y, int x,  WINDOW * mapWin){
    curs_set(0);
    this->sizeY = y;
    this->sizeX = x;
    this->mapWin = mapWin;
    this->enteranceSel = 0;
    
}
CMap::CMap(){}


void CMap::buy (int index){
   

    DynamicVec.push_back(std::make_unique<CHogRider>(EnteranceCords[this->enteranceSel]%this->sizeX,EnteranceCords[this->enteranceSel] / this->sizeX));
    calculatePath(DynamicVec.back().get());

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



