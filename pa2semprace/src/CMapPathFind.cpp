#pragma once
#include "CMap.hpp"
#include "queue"
#include "set"

void CMap::calculatePath( CAttacker * a){
    std::ofstream off("movesTaken.txt");
    int startX = a->x;
    int startY = a->y;
    int cnt = 0;
    int closestExit;
    for (int i = 0;i < mapVec.size(); i++){
        off << "x: " << mapVec[i].get()->xCord << " y: " << mapVec[i].get()->yCord << " total: " << mapVec[i].get()->Index << '\n';


    }
   
    
        int movesTaken = 0;
        std::queue<CCell *> cellsToVisit;
        std::set<int> VisitedCells;
        cellsToVisit.push((mapVec.at((startY*sizeX) + startX ).get()));
        while (!cellsToVisit.empty()){
            CCell * ptr = cellsToVisit.front();
            if (VisitedCells.find(ptr->Index) == VisitedCells.end()) {
                a->path.push_back(std::make_pair(ptr->xCord,ptr->yCord));
                if (ptr->C == 'l') {
                    off << "found exit" << '\n';
                    break;
                    }

                if (ptr->yCord > 0){
                    if (mapVec.at(((ptr->Index) - sizeX)).get()->C == ' '){

                        if (VisitedCells.find(mapVec.at(((ptr->Index) - sizeX)).get()->Index) == VisitedCells.end()){
                            
                            //a->path.push_back(0);
                            cellsToVisit.push(mapVec.at(ptr->Index - sizeX).get());
                        }
                    }
                }
                if (ptr->xCord < sizeX+1){
                    if (mapVec.at((ptr->Index + 2)).get()->C == ' '){
                        if (VisitedCells.find(mapVec.at(((ptr->Index) + 2)).get()->Index) == VisitedCells.end())
                        {
                            
                            //a->path.push_back(1);
                            cellsToVisit.push(mapVec.at(ptr->Index + 1).get());
                        }   
                    }
                }
                if (ptr->yCord < sizeY){
                    if (mapVec.at((ptr->Index + sizeX)).get()->C == ' '){
                       if (VisitedCells.find(mapVec.at(((ptr->Index) + sizeX)).get()->Index) == VisitedCells.end())
                       {
                           
                            //a->path.push_back(2);
                            cellsToVisit.push(mapVec.at(ptr->Index + sizeX).get());
                        }      
                    }
                }
                if (ptr->xCord > 0){
                    if (mapVec.at((ptr->Index) - 1).get()->C == ' '){
                        if (VisitedCells.find(mapVec.at(((ptr->Index) - 1)).get()->Index) == VisitedCells.end())
                        {
                            
                            //a->path.push_back(3);
                            cellsToVisit.push(mapVec.at(ptr->Index - 1).get());
                        }   
                    }
                }
            
            off << "x: " << cellsToVisit.front()->xCord << " y: " << cellsToVisit.front()->yCord << '\n';
            }
            VisitedCells.emplace(ptr->Index);
            cellsToVisit.pop();
            movesTaken++;
            if (movesTaken > 3000) break;
            
        }
        off << movesTaken << '\n';
        off <<"visited : " << VisitedCells.size() << '\n';
        for (auto i : VisitedCells){
            off << i << '\n' ;
        }
        
    
    
}