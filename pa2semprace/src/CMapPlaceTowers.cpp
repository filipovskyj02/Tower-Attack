
#include "CMap.hpp"
#include "CTower2.hpp"

void CMap::placeTowers(int n, std::vector<TowerConf>& a){
    
    if (!n) return;
    std::vector<std::unique_ptr<CAttacker>> ShortestPaths;
    std::sort(a.begin(),a.end(),[](const TowerConf &a, const TowerConf &b){if (a.range > b.range) return true;
    return false;});

    int towerTypeRatio = 2;
    int towersPerType = n / towerTypeRatio;
    
    for (int i = 0; i < enteranceCnt; i++){
         ShortestPaths.push_back(std::make_unique<CMapScout>(EnteranceCords[i]%this->sizeX,EnteranceCords[i] / this->sizeX));
         calculatePath(ShortestPaths[i].get(),EXIT_LETTER);
        
    }
    int shortestPath = ShortestPaths.at(0).get()->path.size();
    for (int j = 1; j < enteranceCnt; j++){
        if (ShortestPaths.at(j).get()->path.size() < (unsigned)shortestPath ) shortestPath = ShortestPaths.at(j).get()->path.size();
    }
    shortestPath = shortestPath/(n+1);
    for (int k = 0; k < n; k++){
        auto f = ShortestPaths[k%enteranceCnt].get()->path[shortestPath*k + shortestPath];
        if (k < towersPerType- 1) TowerVec.push_back(std::make_unique<CLaserTurret>(f.first,f.second, a[0]));
        else if (k >= towersPerType- 1 and a.size() > 1)  TowerVec.push_back(std::make_unique<CTower2>(f.first,f.second,a[1]));

        mapVec[(f.first) + (f.second)*sizeX].get()->C = TOWER_LETTER;


    }
}

