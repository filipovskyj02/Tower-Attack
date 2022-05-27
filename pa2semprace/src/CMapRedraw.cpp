#pragma once
#include "CMap.hpp"

void CMap::redraw (WINDOW * mapWin){
   
    wclear(mapWin);
    box(mapWin,0,0);
    std::pair<int,int> currCords;
    currCords.first = currCords.second = 0;
      
    
    for (unsigned int y = 0; y < mapVec.size(); y++){
        bool found = false;
      
        if (currCords.first == sizeX)
        {
            currCords.first = 0;
            currCords.second++;
        }
        for (unsigned int i = 0; i < DynamicVec.size(); i++){
            
            if (currCords.first == DynamicVec[i].get()->x and currCords.second == DynamicVec[i].get()->y) {
                DynamicVec[i].get()->draw(mapWin);
                
                found = true;
                break;
                }
        }

        if (!found)mapVec[y].get()->draw(mapWin);
        currCords.first++;
        
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
