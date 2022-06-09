#include "CTank.hpp"



CTank::CTank(int x,int y,AttackerConf & a ) : CAttacker('h') {
    this->x = x;
    this->y = y;
    this->runSpeed = a.runSpeed;
    this->damage = a.damage;
    this->pathIndex = 0;
    this->health = this->fullHealth = a.hp;
    this->moveCnt = 0;
    this->range = a.range;
    this->fireFrequency = a.freq;
    if (this->fireFrequency == 0)this->fireFrequency = 1;
    this->attackerIndex = 1;
    
    
   
}

void CTank::draw(WINDOW * map){
    
    if (this->shotsCnt % this->fireFrequency != 0) this->shotsCnt++;
    start_color();
    if (this->shotsCnt % this->fireFrequency == 0) {
        init_pair(9, COLOR_BLACK, COLOR_GREEN);
        wattron(map,COLOR_PAIR(9));
        waddch(map,'t');
        wattroff(map,COLOR_PAIR(9));

    }
    else {
        init_pair(8, COLOR_BLACK, COLOR_YELLOW);
        wattron(map,COLOR_PAIR(8));
        waddch(map,'t');
        wattroff(map,COLOR_PAIR(8));
        }
    

    
 }
 
 void CTank::move(){
    if (this->health <= 0) {
       
        this->dead = true;
        return;
    }
    if ((unsigned)pathIndex < path.size()  ){
        if (this->moveCnt % runSpeed == 0){
        this->x = this->path.at(pathIndex).first;
        this->y = this->path.at(pathIndex).second;
   
        this->pathIndex += 1;  
        }
        this->moveCnt++;  
    }
    
    
    
     
 }
 void CTank::attack(CTower * enemy){
      if (this->shotsCnt % this->fireFrequency == 0) {
        this->shotsCnt = 1;
        enemy->health -= this->damage;
        }
     
 }

 char CTank::whatToFind(){
         return 'T';
}