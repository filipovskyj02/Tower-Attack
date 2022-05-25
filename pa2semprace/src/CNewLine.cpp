#include "CNewLine.hpp"



CNewLine::CNewLine(char c) : CCell(c) {
   
}

void CNewLine::draw(WINDOW * map){
    waddch(map,'\n');
    
 }