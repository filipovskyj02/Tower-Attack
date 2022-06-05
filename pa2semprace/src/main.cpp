#include "CMenu.hpp"
#include "CGame.hpp"

int main () {

CMenu test;

while (test.exit != true) {
    test.draw(30,30);
    if (test.contin() == true){
        if (test.loadedFile >= 0)
        CGame Gem(test.mapChoice,test.confChoice,test.loadedFile);
        else CGame Gem(test.mapChoice,test.confChoice,-1);
    }
}
return EXIT_SUCCESS;
}
