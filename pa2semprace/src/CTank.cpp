#include "CTank.hpp"



CTank::CTank(int x,int y) : CAttacker('h') {
    this->x = x;
    this->y = y;
    this->runSpeed = 1;
    this->damage = 30;
    this->pathIndex = 0;
    this->health = this->fullHealth = 5000;
    this->moveCnt = 0;
    this->range = 100;
    this->fireFrequency = 5;
    
   
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
    if (pathIndex < path.size()  ){
        if (this->moveCnt % 5 == 0){
        this->x = this->path.at(pathIndex).first;
        this->y = this->path.at(pathIndex).second;
   
        this->pathIndex += this->runSpeed;  
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