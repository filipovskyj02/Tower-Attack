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
      
    
    for (unsigned int y = 0; y < mapVec.size(); y++)
    
     mapVec[y].get()->draw(mapWin);
    
    wrefresh(mapWin);
    
    return;
    
    

}
void CMap::loadMap(){
      std::ifstream fin("map.txt");
    
    char element;
    while (fin >> std::noskipws >> element)
    {
        
        mapVec.push_back(std::make_unique<CCell>(element));
    }
}