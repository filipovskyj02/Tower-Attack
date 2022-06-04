#include "CMenu.hpp"
#include "CGame.hpp"

int main () {

CMenu test;

while (test.exit != true) {
    test.draw(30,30);
    if (test.contin() == true)
    CGame Gem(test.mapChoice,test.confChoice);
    
}
return EXIT_SUCCESS;
}
