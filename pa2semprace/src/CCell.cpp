#include "CCell.hpp"

CCell::CCell (char c, int total, int x, int y){
    this->C = c;
    this->Index = total;
    this->xCord = x;
    this->yCord = y;
    this->towerIndex = 0;
    this->AttackerIndex = 0;
    this->pathIndex = std::make_pair(0,0);
    this->healthDraw = 0;
    
    
}
