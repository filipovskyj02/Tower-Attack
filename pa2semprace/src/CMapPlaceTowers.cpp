#pragma once
#include "CMap.hpp"

void CMap::placeTowers(){
    for (int i = 0; i < 5; i++){
        TowerVec.push_back(std::make_unique<CLaserTurret>(i+2,i+2));
        

    }

}