
#include "SConf.hpp"


AttackerConf::AttackerConf(int runSpeed, int dmg, int hp, int rg, int freq){
        this-> runSpeed = runSpeed;
        this-> damage = dmg;
        this-> hp = hp;
        this-> range = rg;
        this-> freq = freq;
    }

TowerConf::TowerConf(int dmg, int hp, int range, int freq){
    this->damage = dmg;
    this->hp = hp;
    this->range = range;
    this->freq = freq;


}