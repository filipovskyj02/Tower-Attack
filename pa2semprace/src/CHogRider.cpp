#include "CHogRider.hpp"



CHogRider::CHogRider(int x,int y,AttackerConf & a) : CAttacker('h') {
    this->x = x;
    this->y = y;
    this->runSpeed = a.runSpeed;
    this->damage = a.damage;
    this->pathIndex = 0;
    this->health = this->fullHealth = a.hp;
    this->moveCnt = 0;
    this->range = a.range;
    this->fireFrequency = a.freq;
    this->attackerIndex = 0;
    
   
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
         if (this->moveCnt % this->runSpeed == 0){
            this->x = this->path.at(pathIndex).first;
            this->y = this->path.at(pathIndex).second;
            this->pathIndex += 1;
        }

        this->moveCnt++;  
            
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