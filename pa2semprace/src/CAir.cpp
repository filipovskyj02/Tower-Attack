#include "CAir.hpp"



CAir::CAir(char c) : CCell(c) {
   
}

void CAir::draw(WINDOW * map){
    waddch(map,' ');
 }