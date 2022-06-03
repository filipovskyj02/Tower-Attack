#include "CMenu.hpp"
#include "CGame.hpp"

int main () {

CMenu test;

while (test.exit != true) {
    test.draw(30,30);
    if (test.contin() == true)
    CGame Gem(22,30,test.mapChoice);
    
}
return EXIT_SUCCESS;
}
