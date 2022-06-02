#pragma once
#include "CMap.hpp"

void CMap::redraw (WINDOW * mapWin){
   
    wclear(mapWin);
    box(mapWin,0,0);
    std::pair<int,int> currCords;
    currCords.first = currCords.second = 0;
    for (unsigned int j = 0; j < mapVec.size(); j++){
        mapVec[j].get()->towerIndex = -10;
        mapVec[j].get()->AttackerIndex = -10;
        mapVec[j].get()->healthDraw = -10;
       
    }
    for (unsigned int i = 0; i < DynamicVec.size(); i++){
        auto ptr = mapVec[((DynamicVec[i].get()->y) * sizeX) + DynamicVec[i].get()->x].get();
        ptr->AttackerIndex = i;
        auto ptr1 = mapVec[((DynamicVec[i].get()->y-1) * sizeX) + DynamicVec[i].get()->x].get();
        ptr1->healthDraw = (DynamicVec[i].get()->health*10)/(DynamicVec[i].get()->fullHealth+1);
          

    }

    for (unsigned int i = 0; i < TowerVec.size(); i++){
        auto ptr = mapVec.at(((TowerVec[i].get()->y) * sizeX) + TowerVec[i].get()->x).get();
        ptr->towerIndex = i;
        auto ptr1 = mapVec[((TowerVec[i].get()->y-1) * sizeX) + TowerVec[i].get()->x].get();
        ptr1->healthDraw = (TowerVec[i].get()->health*10)/(TowerVec[i].get()->fullHealth+1);   
    }

    for (unsigned int y = 0; y < mapVec.size(); y++){
        auto ptr = mapVec[y].get();
        if (ptr->AttackerIndex >= 0) DynamicVec[ptr->AttackerIndex].get()->draw(mapWin);
        else if (ptr->towerIndex >= 0) TowerVec[ptr->towerIndex].get()->draw(mapWin);
        else ptr->draw(mapWin);
        
    }
    

    for (unsigned int i = 0; i < DynamicVec.size(); i++){
           
            
             if (DynamicVec[i].get()->left == true){

                DynamicVec[i].reset();
                DynamicVec.erase(DynamicVec.begin()+i);
                }
            else if (DynamicVec[i].get()->dead == false)
                DynamicVec[i].get()->move();
            
            
            else {
                
                DynamicVec[i].reset();
                DynamicVec.erase(DynamicVec.begin()+i);
                }
        }
    for (unsigned int i = 0; i < TowerVec.size(); i++){
        if (TowerVec[i].get()->destroyed == true){
            TowerVec[i].reset();
            TowerVec.erase(TowerVec.begin()+i);

        }


    }
    
    wrefresh(mapWin);
    return;
    
    

}
