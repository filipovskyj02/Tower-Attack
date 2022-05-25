#include "CCell.hpp"

CCell::CCell (char c){
    this->C = c;

}

void CCell::draw(WINDOW * map){
    waddch(map,this->C);

}

