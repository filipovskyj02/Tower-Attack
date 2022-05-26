#include "CMap.hpp"


CMap::CMap (int y, int x,  WINDOW * mapWin){
    curs_set(0);

    
    this->sizeY = y;
    this->sizeX = x;
    this->redrawCnt = 0;
    this->mapWin = mapWin;
    





}
CMap::CMap(){}

void CMap::redraw (WINDOW * mapWin){
   
    wclear(mapWin);
    box(mapWin,0,0);
    std::pair<int,int> currCords;
    currCords.first = currCords.second = 0;
      
    
    for (unsigned int y = 0; y < mapVec.size(); y++){
        bool found = false;
        currCords.first++;
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
    
        
    }
    for (unsigned int i = 0; i < DynamicVec.size(); i++){
            DynamicVec[i].get()->move();
            
        }
    
    wrefresh(mapWin);
    return;
    
    

}
void CMap::loadMap(){
      std::ifstream fin("map.txt");
    
    char element;
    while (fin >> std::noskipws >> element)
    {
        if (element == ' '){
            if (mapVec.back().get()->C == '\n'){
                mapVec.push_back(std::make_unique<CEnterance>());
            }
            else mapVec.push_back(std::make_unique<CAir>(element));
        }
        else if (element == 'x')mapVec.push_back(std::make_unique<CWall>(element));
        else if (element == '\n'){
        
            if (mapVec.back().get()->C == ' ') mapVec.back()=(std::make_unique<CExit>());
            mapVec.push_back(std::make_unique<CNewLine>(element));
            }
    }
}
void CMap::buy (int index){
    std::pair<int,int> currCords;
    currCords.first = currCords.second = 0;
    for (unsigned int i = 0;i < mapVec.size(); i++ ){
        if (typeid(mapVec[i].get()) == typeid(CEnterance))break;
    
        
        currCords.first++;
        if (currCords.first == sizeX)
        {
            currCords.first = 0;
            currCords.second++;
        }
    }

    DynamicVec.push_back(std::make_unique<CHogRider>(10,10));




}