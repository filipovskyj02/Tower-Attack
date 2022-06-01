#include "CTower.hpp"

CTower::CTower(int x, int y){
    this->x = x;
    this->y = y;
    this->destroyed = false;
    this->shotsCnt = 1;
}