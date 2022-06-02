#pragma once
#include "CMap.hpp"

void CMap::loadMap(int & loadedX,  int & loadedY){
    std::ifstream fin("maze2.txt");
    
    
    char element;
    
    int width = 1;
    int lineCtr = 0;
    while (fin >> std::noskipws >> element)
    {
        int index = width - 1;
        int x = index % sizeX;
        int y = index / sizeX;
        
        switch (element){
            case AIR_LETTER:
                if (mapVec.back().get()->C == '\n'){
                    mapVec.push_back(std::make_unique<CEnterance>(index,x,y));
                    EnteranceCords.push_back(width);
                }
                else mapVec.push_back(std::make_unique<CAir>(index,x,y));
                break;
            case WALL_LETTER:
                mapVec.push_back(std::make_unique<CWall>(index,x,y));
                break;
            case '\n':
                if (lineCtr == 0) this->sizeX = width ;
                    lineCtr++;
                if (mapVec.back().get()->C == AIR_LETTER) mapVec.back()=(std::make_unique<CExit>(index,x,y));
                
                mapVec.push_back(std::make_unique<CNewLine>(index,x,y));
                ExitCords.push_back(width);
                break;
                    
            }
        width++;


        }
        
    loadedX = this->sizeX;
    loadedY = (width - 1) / this->sizeX;
    this->sizeY = loadedY;
    this->enteranceCnt = EnteranceCords.size();
    
}