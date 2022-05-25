#include "CEnterance.hpp"



CEnterance::CEnterance() : CCell('e') {
   
}

void CEnterance::draw(WINDOW * map){
    start_color();
    init_pair(1, COLOR_BLACK, COLOR_BLUE);
    wattron(map,COLOR_PAIR(1));
    waddch(map,' ');
    wattroff(map,COLOR_PAIR(1));
 }