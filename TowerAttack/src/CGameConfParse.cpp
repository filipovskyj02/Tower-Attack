#include "CGame.hpp"

bool CGame::parseFile(int confChoice){
    
    std::vector<std::string> Options = {"hard.txt", "medium.txt", "easy.txt","free.txt"};
    std::string location ={"examples/Configurations/"};
    std::ifstream myfile;
    myfile.open((location+Options[confChoice]).c_str());
    std::string name, cost;
    std::string a,b,c,d,e;
    
    std::string line;
    
   

   if(!myfile.is_open()) {
      
      return false;
   }
    getline(myfile, line);
    std::stringstream str(line);
    str >> a >> b >> c >> d;
    this->playerMoney = stoi(a);
    this->towerAmount = stoi(b);
    this->minHealthToWin = stoi(c);
    this->minDmgToWin = stoi(d);

    while(getline(myfile, line)) {
        if (line[0] == '#') break;
        std::stringstream str(line);
        str >> name >> cost >> a >> b >> c >> d >> e ;
        this->NameCost.push_back(std::make_pair(name,cost));
        this->att.emplace_back(AttackerConf(stoi(a),stoi(b),stoi(c),stoi(d),stoi(e)));
    }
    while(getline(myfile, line)) {
        
        std::stringstream str(line);
        str >> a >> b >> c >> d >> e;
       
        this->tww.emplace_back(TowerConf(stoi(a),stoi(b),stoi(c),stoi(d)));
    }
    myfile.close();
    if (NameCost.empty() or att.empty() or tww.empty()) return false;
    return true;

}
