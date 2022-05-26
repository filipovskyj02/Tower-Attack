#include "CHogRider.hpp"



CHogRider::CHogRider(int x,int y) : CAttacker('h') {
    this->x = x;
    this->y = y;
    this->runSpeed = 1;
    this->damage = 100;
    this->pathIndex = 1;
   
}

void CHogRider::draw(WINDOW * map){
    start_color();
    init_pair(4, COLOR_BLACK, COLOR_GREEN);
    wattron(map,COLOR_PAIR(4));
    waddch(map,'h');
    wattroff(map,COLOR_PAIR(4));
    
    
    
 }
 int CHogRider::speed(void){
     return this -> runSpeed;
 }
 void CHogRider::move(){
       
     if (this->path.at(pathIndex)== 1)
        y--;
    else 
        x++;
    pathIndex++;    
      
     
 }