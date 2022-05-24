#pragma once
#include "CCell.hpp"
class CAttacker : public CCell
{
public:

    int damage;
    int health;
    int speed;
    int range;

    
    virtual void Move() = 0;
    virtual void trade() = 0;
    


};

