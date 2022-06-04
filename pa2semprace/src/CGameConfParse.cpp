#include "CGame.hpp"

void CGame::parseFile(){
    
    std::ofstream of("outsave.txt");
    std::string name, cost;
    std::string a,b,c,d,e;
    
    std::string line;
    std::ifstream myfile;
    myfile.open("save2.txt");

   if(!myfile.is_open()) {
      
      exit(EXIT_FAILURE);
   }
    while(getline(myfile, line)) {
        if (line[0] == '#') break;
        std::stringstream str(line);
        str >> name >> cost >> a >> b >> c >> d >> e ;
        NameCost.push_back(std::make_pair(name,cost));
        att.emplace_back(AttackerConf(stoi(a),stoi(b),stoi(c),stoi(d),stoi(e)));
    }
    while(getline(myfile, line)) {
        
        std::stringstream str(line);
        str >> a >> b >> c >> d >> e;
       
        tww.emplace_back(TowerConf(stoi(a),stoi(b),stoi(c),stoi(d)));
    }
    myfile.close();
    

}
