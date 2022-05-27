#include "CCellBasic.hpp"



CAir::CAir(int total, int x, int y) : CCell(' ',total,x,y){}
CEnterance::CEnterance(int total, int x, int y) : CCell('e',total,x,y){}
CExit::CExit(int total, int x, int y) : CCell('l',total,x,y){}
CNewLine::CNewLine(int total, int x, int y) : CCell('\n',total,x,y){}
CWall::CWall(int total, int x, int y) : CCell('x',total,x,y){}

void CAir::draw(WINDOW * map){
    waddch(map,' ');
}


void CEnterance::draw(WINDOW * map){
    


    start_color();
    init_pair(1, COLOR_BLACK, COLOR_BLUE);
    init_pair(3, COLOR_BLACK, COLOR_GREEN);
    if (this->C == 's'){
    wattron(map,COLOR_PAIR(3));
    waddch(map,' ');
    wattroff(map,COLOR_PAIR(3));
    return;
    }
    wattron(map,COLOR_PAIR(1));
    waddch(map,' ');
    wattroff(map,COLOR_PAIR(1));
    
}


void CExit::draw(WINDOW * map){
    start_color();
    init_pair(2, COLOR_BLACK, COLOR_RED);
    wattron(map,COLOR_PAIR(2));
    waddch(map,' ');
    wattroff(map,COLOR_PAIR(2));
    }



void CNewLine::draw(WINDOW * map){
    waddch(map,'\n');
    
}



void CWall::draw(WINDOW * map){
    waddch(map,'x');
    
}