#include "CLaserTurret.hpp"

CLaserTurret::CLaserTurret(int x, int y) : CTower(x,y){};

void CLaserTurret::draw(WINDOW * map){
    start_color();
    init_pair(5, COLOR_BLACK, COLOR_RED);
    wattron(map,COLOR_PAIR(5));
    waddch(map,'T');
    wattroff(map,COLOR_PAIR(5));
}