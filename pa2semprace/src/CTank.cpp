#include "CTank.hpp"



CTank::CTank(int x,int y) : CAttacker('h') {
    this->x = x;
    this->y = y;
    this->runSpeed = 1;
    this->damage = 100;
    this->pathIndex = 0;
    this->health = 2000;
    
   
}

void CTank::draw(WINDOW * map){
    start_color();
    init_pair(4, COLOR_BLACK, COLOR_GREEN);
    wattron(map,COLOR_PAIR(4));
    waddch(map,'J');
    wattroff(map,COLOR_PAIR(4));
    
    
    
 }
 int CTank::speed(void){
     return this -> runSpeed;
 }
 void CTank::move(){
    if (this->health <= 0) {
        this->left = true;
        return;
    }
    
    if (pathIndex < path.size()  ){
        if (this->moveCnt % 5 == 0){
        this->x = this->path.at(pathIndex).first;
        this->y = this->path.at(pathIndex).second;
   
        pathIndex += this->runSpeed;  
        }
        this->moveCnt++;  
    }
    else this->left = true;
    
     
 }