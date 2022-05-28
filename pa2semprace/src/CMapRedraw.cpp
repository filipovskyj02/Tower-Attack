#pragma once
#include "CMap.hpp"

void CMap::redraw (WINDOW * mapWin){
   
    wclear(mapWin);
    box(mapWin,0,0);
    std::pair<int,int> currCords;
    currCords.first = currCords.second = 0;
    for (unsigned int j = 0; j < mapVec.size(); j++){
        mapVec[j].get()->towerIndex = - 10;
        mapVec[j].get()->AttackerIndex = - 10;
    }
    for (unsigned int i = 0; i < DynamicVec.size(); i++){
        mapVec[((DynamicVec[i].get()->y) * sizeX) + DynamicVec[i].get()->x].get()->AttackerIndex = i;     
    }

    for (unsigned int i = 0; i < TowerVec.size(); i++){
        mapVec[((TowerVec[i].get()->y) * sizeX) + TowerVec[i].get()->x].get()->towerIndex = i;     
    }

    for (unsigned int y = 0; y < mapVec.size(); y++){
        auto ptr = mapVec[y].get();
        if (ptr->AttackerIndex >= 0) DynamicVec[ptr->AttackerIndex].get()->draw(mapWin);
        else if (ptr->towerIndex >= 0) TowerVec[ptr->towerIndex].get()->draw(mapWin);
        else ptr->draw(mapWin);
        
    }
    

    for (unsigned int i = 0; i < DynamicVec.size(); i++){
            if (DynamicVec[i].get()->left == false)
                DynamicVec[i].get()->move();
            else {
                DynamicVec[i].reset();
                DynamicVec.erase(DynamicVec.begin()+i);
                }
            
            
        }
    
    wrefresh(mapWin);
    return;
    
    

}
