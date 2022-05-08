#pragma once
#include "CCell.hpp"
class CTower : public CCell
{
public:
    int damage;
    int health;
    int reloadTime;
    int range;
    
    virtual void trade()=0;


};


