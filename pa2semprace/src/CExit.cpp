#include "CExit.hpp"



CExit::CExit() : CCell('l') {
   
}

void CExit::draw(WINDOW * map){
    start_color();
    init_pair(2, COLOR_BLACK, COLOR_RED);
    wattron(map,COLOR_PAIR(2));
    waddch(map,' ');
    wattroff(map,COLOR_PAIR(2));
 }