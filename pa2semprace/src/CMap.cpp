#include "CMap.hpp"


CMap::CMap (int y, int x,  WINDOW * mapWin){
    curs_set(0);

    
    this->sizeY = y;
    this->sizeX = x;
    
    this->mapWin = mapWin;
    this->enteranceSel = 0;
    
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
      std::ifstream fin("map1.txt");
    
    char element;
    int width = 1;
    int lineCtr = 0;
    while (fin >> std::noskipws >> element)
    {
        if (element == ' '){
            if (mapVec.back().get()->C == '\n'){
               
                mapVec.push_back(std::make_unique<CEnterance>());
                EnteranceCords.push_back(width);
            }
            else mapVec.push_back(std::make_unique<CAir>(element));
        }
        else if (element == 'x')mapVec.push_back(std::make_unique<CWall>(element));
        else if (element == '\n'){
            if (lineCtr == 0) this->sizeX = width;
                lineCtr++;
            if (mapVec.back().get()->C == ' ') mapVec.back()=(std::make_unique<CExit>());
            mapVec.push_back(std::make_unique<CNewLine>(element));
            }
            width++;
    }
    this->enteranceCnt = EnteranceCords.size();
}
void CMap::buy (int index){
    std::pair<int,int> currCords;
    if (!EnteranceCords.empty())

    DynamicVec.push_back(std::make_unique<CHogRider>(EnteranceCords[this->enteranceSel]%this->sizeX,EnteranceCords[this->enteranceSel] / this->sizeX));

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
