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
            if (DynamicVec[i].get()->pathIndex > 99) {
                DynamicVec[i].reset();
                DynamicVec.erase(DynamicVec.begin()+i);
                }
            
        }
    
    wrefresh(mapWin);
    return;
    
    

}
void CMap::loadMap(){
      std::ifstream fin("map2.txt");
    
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
            ExitCords.push_back(width);
            }
            width++;
    }
    this->enteranceCnt = EnteranceCords.size();
}
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
void CMap::calculatePath( CAttacker * a){
    
    int startX = a->x;
    int startY = a->y;
    int cnt = 0;

    while (startX != sizeX and cnt < 100){
    

        if (mapVec.at((startY*sizeX) + startX ).get()->C == ' ' or mapVec.at((startY*sizeX) + startX ).get()->C == 'e') {a->path.push_back(0); startX++;}
        else {a->path.push_back(1); if (startY > 0) startY--;}
        cnt++;
    }
}


