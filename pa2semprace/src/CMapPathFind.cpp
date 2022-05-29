#pragma once
#include "CMap.hpp"
#include "queue"
#include "set"
#include "algorithm"

void CMap::calculatePath( CAttacker * a, char lookingFor){
    std::ofstream off("movesTaken.txt");

    int startX = a->x;
    int startY = a->y;

        int movesTaken = 0;
        std::queue<CCell *> cellsToVisit;
        std::set<int> VisitedCells;
        cellsToVisit.push(mapVec.at((startY*sizeX) + startX ).get());
        while (!cellsToVisit.empty()){
            CCell * ptr = cellsToVisit.front();
            CCell * ptrTmp = nullptr;
            if (VisitedCells.find(ptr->Index) == VisitedCells.end()) {

                
                if (ptr->C == lookingFor) {
                    off << "found exit" << '\n';
                    int cycleCnt = 0;
                    while (ptr->pathIndex.second != 0 and cycleCnt < VisitedCells.size()){
                        a->path.push_back(std::make_pair(ptr->xCord,ptr->yCord));
                        ptr = mapVec.at((ptr->pathIndex.second *sizeX) + ptr->pathIndex.first).get();
                        cycleCnt++;
                        

                    }
                    std::reverse(a->path.begin(),a->path.end());
                    break;
                    }

                if (ptr->yCord > 0){
                     ptrTmp = mapVec.at(((ptr->Index) - sizeX)).get();
                    if (ptrTmp->C == ' ' or ptrTmp->C == lookingFor){

                        if (VisitedCells.find(ptrTmp->Index) == VisitedCells.end()){
                            if(!ptrTmp->pathIndex.second) ptrTmp->pathIndex = std::make_pair(ptr->xCord,ptr->yCord);
                            cellsToVisit.push(ptrTmp);
                        }
                    }
                }
                if (ptr->xCord < sizeX){
                    ptrTmp = mapVec.at(((ptr->Index) + 1)).get();
                    if (ptrTmp->C == ' ' or ptrTmp->C == lookingFor){
                        if (VisitedCells.find(ptrTmp->Index)== VisitedCells.end()){
                            if(!ptrTmp->pathIndex.second) ptrTmp->pathIndex = std::make_pair(ptr->xCord,ptr->yCord);
                            cellsToVisit.push(ptrTmp);
                        }   
                    }
                }
                if (ptr->yCord < sizeY){
                    ptrTmp = mapVec.at((ptr->Index + sizeX)).get();
                    if (ptrTmp->C == ' ' or ptrTmp->C == lookingFor){
                       if (VisitedCells.find(ptrTmp->Index) == VisitedCells.end()){
                            if(!ptrTmp->pathIndex.second) ptrTmp->pathIndex = std::make_pair(ptr->xCord,ptr->yCord);
                            cellsToVisit.push(ptrTmp);
                        }      
                    }
                }
                if (ptr->xCord > 1){
                    ptrTmp = mapVec.at((ptr->Index) - 1).get();
                    if (ptrTmp->C == ' ' or ptrTmp->C == lookingFor){
                        if (VisitedCells.find(ptrTmp->Index) == VisitedCells.end()){
                            if(!ptrTmp->pathIndex.second) ptrTmp->pathIndex = std::make_pair(ptr->xCord,ptr->yCord);
                            cellsToVisit.push(ptrTmp);
                        }   
                    }
                }
            
            off << "x: " << cellsToVisit.front()->xCord << " y: " << cellsToVisit.front()->yCord << '\n';
            }
            VisitedCells.emplace(ptr->Index);
            cellsToVisit.pop();
            
            movesTaken++;
        }
        VisitedCells.clear();
        for (unsigned int i = 0; i < mapVec.size(); i++){
            mapVec[i].get()->pathIndex.first = 0;
            mapVec[i].get()->pathIndex.second = 0;
        }
        
        
    
    
}