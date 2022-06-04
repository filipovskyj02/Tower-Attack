#include "CGame.hpp"

void CGame::saveGame(){
    

    std::vector<std::string> mapOptions = {"Save1.txt", "Save2.txt", "Save3.txt","Save4.txt","Save5.txt"};
    std::string location ={"../examples/Saves/"};
    std::ofstream off;
    off.open((location+mapOptions[this->saveChoice]).c_str());
    off << this->mapChoice << " " << this->confChoice << " " << this->playerMoney << " "<< this->gameMap.alHP<< " " << this->gameMap.alDMG<< " " << this->gameMap.attackersLeft << std::endl;

    for (unsigned int i = 0; i < this->gameMap.DynamicVec.size(); i++){
        auto ptr = this->gameMap.DynamicVec[i].get();
        off << ptr->attackerIndex << " " << ptr->health  << " " << ptr->shotsCnt << " " << ptr->x << " " << ptr->y << std::endl;
    }
    off << "#" << std::endl;
    for (unsigned int i = 0; i < this->gameMap.TowerVec.size(); i++){
        auto ptr = this->gameMap.TowerVec[i].get();
        off << ptr->towerIndex << " " << ptr->health  << " " << ptr->shotsCnt << " " << ptr->x << " " << ptr->y << std::endl;
    }
    off.close();
    return;
}