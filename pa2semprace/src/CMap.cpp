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
      std::ifstream fin("map1.txt");
    
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