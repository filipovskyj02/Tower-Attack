#include "CMapScout.hpp"



CMapScout::CMapScout(int x,int y) : CAttacker('s') {
    this->x = x;
    this->y = y;
    this->runSpeed = 0;
    this->damage = 0;
    this->pathIndex = 0;
   
}
char CMapScout::whatToFind(){
    return 'e';
}


void CMapScout::draw(WINDOW * map){}
 
void CMapScout::move(){}

void CMapScout::attack(CTower * enemy){}

