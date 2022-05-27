#include "CCell.hpp"

CCell::CCell (char c, int total, int x, int y){
    this->C = c;
    this->Index = total;
    this->xCord = x;
    this->yCord = y;
    this->pathIndex = std::make_pair(0,0);
    
}
