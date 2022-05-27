#pragma once
#include "CMap.hpp"

void CMap::loadMap(){
    std::ifstream fin("map2.txt");
    
    char element;
    int width = 1;
    int lineCtr = 0;
    while (fin >> std::noskipws >> element)
    {
        int index = width - 1;
        int x = index % sizeX;
        int y = index / sizeX;
        if (element == ' '){
            if (mapVec.back().get()->C == '\n'){
               
                mapVec.push_back(std::make_unique<CEnterance>(index,x,y));
                EnteranceCords.push_back(width);
            }
            else mapVec.push_back(std::make_unique<CAir>(index,x,y));
        }
        else if (element == 'x')mapVec.push_back(std::make_unique<CWall>(index,x,y));
        else if (element == '\n'){
            if (lineCtr == 0) this->sizeX = width;
                lineCtr++;
            if (mapVec.back().get()->C == ' ') mapVec.back()=(std::make_unique<CExit>(index,x,y));
            mapVec.push_back(std::make_unique<CNewLine>(index,x,y));
            ExitCords.push_back(width);
            }
        width++;
    }
    this->enteranceCnt = EnteranceCords.size();
}