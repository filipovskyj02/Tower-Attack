#include "CJumper.hpp"



CJumper::CJumper(int x,int y,AttackerConf & a) : CAttacker('h') {
    this->x = x;
    this->y = y;
    this->runSpeed = a.runSpeed;
    this->damage = a.damage;
    this->pathIndex = 0;
    this->health = this->fullHealth = a.hp;
    this->moveCnt = 0;
    this->range = a.range;
    this->fireFrequency = a.freq;
    this->attackerIndex = 3;
    if (this->fireFrequency == 0)this->fireFrequency = 1;
    
   
}

void CJumper::draw(WINDOW * map){
    
    
    if (this->shotsCnt % this->fireFrequency != 0) this->shotsCnt++;
    start_color();
    if (this->shotsCnt % this->fireFrequency == 0) {
        init_pair(9, COLOR_BLACK, COLOR_GREEN);
        wattron(map,COLOR_PAIR(9));
        waddch(map,'j');
        wattroff(map,COLOR_PAIR(9));

    }
    else {
        init_pair(8, COLOR_BLACK, COLOR_YELLOW);
        wattron(map,COLOR_PAIR(8));
        waddch(map,'j');
        wattroff(map,COLOR_PAIR(8));
        }
    
    
    
    
 }

 void CJumper::move(){
     if (this->health <= 0) {
       
        this->dead = true;
        return;
    }
    if ((unsigned)pathIndex < path.size()  ){
         if (this->moveCnt % this->runSpeed == 0){
            this->x = this->path.at(pathIndex).first;
            this->y = this->path.at(pathIndex).second;
            if ((unsigned)(pathIndex + 8) < path.size())
            this->pathIndex += 8;
            else this->pathIndex = (int)path.size() - 1;
        }

        this->moveCnt++;  
            
    }    
    
     
 }
 void CJumper::attack(CTower * enemy){
     //doesnt attack, just tries to jump into an exit
     
 }

 char CJumper::whatToFind(){
         return 'e';


}