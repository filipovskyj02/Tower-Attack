#include "CLongRange.hpp"



CLongRange::CLongRange(int x,int y,AttackerConf & a) : CAttacker('h') {
    this->x = x;
    this->y = y;
    this->runSpeed = a.runSpeed;
    this->damage = a.damage;
    this->pathIndex = 0;
    this->health = this->fullHealth = a.hp;
    this->moveCnt = 0;
    this->range = a.range;
    this->fireFrequency = a.freq;
    this->attackerIndex = 2;
    if (this->fireFrequency == 0)this->fireFrequency = 1;
    
   
}

void CLongRange::draw(WINDOW * map){
    
    
    if (this->shotsCnt % this->fireFrequency != 0) this->shotsCnt++;
    start_color();
    if (this->shotsCnt % this->fireFrequency == 0) {
        init_pair(9, COLOR_BLACK, COLOR_GREEN);
        wattron(map,COLOR_PAIR(9));
        waddch(map,'s');
        wattroff(map,COLOR_PAIR(9));

    }
    else {
        init_pair(8, COLOR_BLACK, COLOR_YELLOW);
        wattron(map,COLOR_PAIR(8));
        waddch(map,'s');
        wattroff(map,COLOR_PAIR(8));
        }
    
    
    
    
 }

 void CLongRange::move(){
    if (this->health <= 0) {
       
        this->dead = true;
        return;
    }
  //doesnt move 
    
    
     
 }
 void CLongRange::attack(CTower * enemy){
     if (this->shotsCnt % this->fireFrequency == 0) {
        this->shotsCnt = 1;
        enemy->health -= this->damage;
        }
     
     
 }

 char CLongRange::whatToFind(){
         return 'e';


}