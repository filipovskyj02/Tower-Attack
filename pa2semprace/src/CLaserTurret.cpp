#include "CLaserTurret.hpp"

CLaserTurret::CLaserTurret(int x, int y) : CTower(x,y){
    this->damage = 10;
    this->fireFrequency = 5;
    this->health = this->fullHealth = 2000;
    this->range = 100;
    };

void CLaserTurret::draw(WINDOW * map){
    if(this->health <= 0)this->destroyed++;
    if (this->shotsCnt % this->fireFrequency != 0) this->shotsCnt++;
    start_color();
    if (this->shotsCnt % this->fireFrequency == 0) {
        init_pair(10, COLOR_BLACK, COLOR_RED);
        wattron(map,COLOR_PAIR(10));
        waddch(map,'L');
        wattroff(map,COLOR_PAIR(10));

    }
    else {
        init_pair(11, COLOR_BLACK, COLOR_MAGENTA);
        wattron(map,COLOR_PAIR(11));
        waddch(map,'L');
        wattroff(map,COLOR_PAIR(11));
        }
    
}

void CLaserTurret::attack(CAttacker * enemy){
   
    
    if (this->shotsCnt % this->fireFrequency == 0) {
        this->shotsCnt = 1;
        enemy->health -= this->damage;
        }

}