#include "CWall.hpp"



CWall::CWall(char c) : CCell(c) {
   
}

void CWall::draw(WINDOW * map){
    waddch(map,'x');
    
 }