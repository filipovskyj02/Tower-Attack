#pragma once
#include "CGame.hpp"
class CMap
{
public:
    std::vector<CCell *> Field;
    void draw();
    //goes through the whole vector and finds which ranges intersect
    void intersect();




};


