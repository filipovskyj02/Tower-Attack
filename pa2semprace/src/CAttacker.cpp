#include "CAttacker.hpp"


CAttacker::CAttacker (char c){
    this->C = c;
    this->path.push_back(std::make_pair(1,1));

}
