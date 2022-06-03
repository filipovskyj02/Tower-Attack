#include "CHogRider.hpp"



CHogRider::CHogRider(int x,int y) : CAttacker('h') {
     this->x = x;
    this->y = y;
    this->runSpeed = 1;
    this->damage = 100;
    this->pathIndex = 0;
    this->health = this->fullHealth = 500;
    this->moveCnt = 0;
    this->range = 4;
    this->fireFrequency = 1;
    
   
}

void CHogRider::draw(WINDOW * map){
    
    
    if (this->shotsCnt % this->fireFrequency != 0) this->shotsCnt++;
    start_color();
    if (this->shotsCnt % this->fireFrequency == 0) {
        init_pair(9, COLOR_BLACK, COLOR_GREEN);
        wattron(map,COLOR_PAIR(9));
        waddch(map,'h');
        wattroff(map,COLOR_PAIR(9));

    }
    else {
        init_pair(8, COLOR_BLACK, COLOR_YELLOW);
        wattron(map,COLOR_PAIR(8));
        waddch(map,'h');
        wattroff(map,COLOR_PAIR(8));
        }
    
    
    
    
 }

 void CHogRider::move(){
    if (this->health <= 0) {
       
        this->dead = true;
        return;
    }
    if (pathIndex < path.size()  ){
     
        this->x = this->path.at(pathIndex).first;
        this->y = this->path.at(pathIndex).second;
   
        pathIndex += this->runSpeed;    
    }
    
    
     
 }
 void CHogRider::attack(CTower * enemy){
     if (this->shotsCnt % this->fireFrequency == 0) {
        this->shotsCnt = 1;
        enemy->health -= this->damage;
        }
     
     
 }

 char CHogRider::whatToFind(){
         return 'l';


}