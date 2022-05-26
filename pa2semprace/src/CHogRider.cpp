#include "CHogRider.hpp"



CHogRider::CHogRider(int x,int y) : CAttacker('h') {
    this->x = x;
    this->y = y;
    this->runSpeed = 1;
    this->damage = 100;
   
}

void CHogRider::draw(WINDOW * map){
    waddch(map,'h');
    
    
 }
 int CHogRider::speed(void){
     return this -> runSpeed;
 }
 void CHogRider::move(){
     this->x++;
 }