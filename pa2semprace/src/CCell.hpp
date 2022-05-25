#include "ncurses.h"

class CCell{
    public:
    char C;
    CCell(char C);
     
    void draw(WINDOW * map);

};