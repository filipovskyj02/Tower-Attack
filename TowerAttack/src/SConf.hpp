#pragma once
struct AttackerConf{
    int runSpeed;
    int damage;
    int hp;
    int range;
    int freq; 
    
    AttackerConf(int runSpeed, int dmg, int hp, int rg, int freq);
    AttackerConf();
};

struct TowerConf{
    int damage;
    int hp;
    int range;
    int freq; 

    TowerConf(int dmg, int hp, int range, int freq);
    TowerConf();
};
