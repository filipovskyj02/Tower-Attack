#include "CGame.hpp"

void CGame::saveGame(){
    

    std::vector<std::string> mapOptions = {"Save1.txt", "Save2.txt", "Save3.txt","Save4.txt","Save5.txt"};
    std::string location ={"examples/Saves/"};
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

void CGame::loadSave(int loadFile){
    std::vector<std::string> mapOptions = {"Save1.txt", "Save2.txt", "Save3.txt","Save4.txt","Save5.txt"};
    std::string location ={"examples/Saves/"};
    std::ifstream in;
    std::string line;
    int a,b,c,d,e,f;
    in.open((location+mapOptions[loadFile]).c_str());
    getline(in, line);
    std::stringstream str(line);
    str >> a >> b >> c >> d >> e >> f;
    this->mapChoice = a;
    this->confChoice = b;
    if (!this->parseFile(this->confChoice)) return;
        this->gameMap = CMap(mapChoice);
        this->gameMap.loadMap(this->row_width,this->collum_height);
    
    this->playerMoney = c;
    this->gameMap.alHP = d;
    this->gameMap.alDMG = e;
    this->gameMap.attackersLeft = f;
    int attackerConfLoaded = this->att.size();
    int towerConfLoaded = this->tww.size();
    if (!attackerConfLoaded or !towerConfLoaded) return;

    while(getline(in, line)) {
        if (line[0] == '#') break;
        std::stringstream str(line);
        str >> a >> b >> c >> d >> e;
    
        switch (a){
            case 0:
                this->gameMap.DynamicVec.push_back(std::make_unique<CHogRider>(d,e,this->att[0]));
            case 1:
                if (attackerConfLoaded<2) break;
                this->gameMap.DynamicVec.push_back(std::make_unique<CTank>(d,e,this->att[1]));
        }
        auto ptr = this->gameMap.DynamicVec.back().get();
        ptr->health = b;
        ptr->shotsCnt = c;
       

        
    }
    
    while(getline(in, line)) {
        
        std::stringstream str(line);
        str >> a >> b >> c >> d >> e;
        switch (a){
            case 0:
                this->gameMap.TowerVec.push_back(std::make_unique<CLaserTurret>(d,e,this->tww[0]));
            case 1:
                this->gameMap.TowerVec.push_back(std::make_unique<CTower2>(d,e,this->tww[1]));
            
        }
        if (this->gameMap.TowerVec.empty()) break;
        auto ptr = this->gameMap.TowerVec.back().get();
        ptr->health = b;
        ptr->shotsCnt = c;
        

        
    }
    for (unsigned int i = 0; i < this->gameMap.TowerVec.size(); i++){
        auto ptr = this->gameMap.TowerVec[i].get();
        this->gameMap.mapVec[(ptr->y * this->gameMap.sizeX) + ptr->x].get()->C = TOWER_LETTER;

    }

    for (unsigned int i = 0; i < this->gameMap.DynamicVec.size(); i++){
        this->gameMap.calculatePath( this->gameMap.DynamicVec[i].get(),  this->gameMap.DynamicVec[i].get()->whatToFind());
       
    }
    return;


}