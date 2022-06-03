#pragma once
#include "CMap.hpp"

void CMap::placeTowers(int n){
    std::vector<std::unique_ptr<CAttacker>> ShortestPaths;
    off << "Enterance cnt : " << enteranceCnt << std::endl;
    for (unsigned int i = 0; i < enteranceCnt; i++){
         ShortestPaths.push_back(std::make_unique<CMapScout>(EnteranceCords[i]%this->sizeX,EnteranceCords[i] / this->sizeX));
         calculatePath(ShortestPaths[i].get(),EXIT_LETTER);
         off << "lenght of path " << ShortestPaths[i].get()->path.size() << std::endl;
    }
    int shortestPath = ShortestPaths.at(0).get()->path.size();
    for (int j = 1; j < enteranceCnt; j++){
        if (ShortestPaths.at(j).get()->path.size() < shortestPath ) shortestPath = ShortestPaths.at(j).get()->path.size();
    }
    shortestPath = shortestPath/(n+1);
    for (int k = 0; k < n; k++){
        auto f = ShortestPaths[k%enteranceCnt].get()->path[shortestPath*k + shortestPath];
        TowerVec.push_back(std::make_unique<CLaserTurret>(f.first,f.second));
        mapVec[(f.first) + (f.second)*sizeX].get()->C = TOWER_LETTER;


    }
}