#include "potal.h"
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>



Potal potal[20] = {

    {"1-0 -> 1-1", 0, 1, {10, 2}},
    {"1-1 -> 1-2", 1, 2, {50, 28}},
    {"1-2 -> 1-3", 2, 3, {98, 2}}

};




void gotoNextMap() {

    player.currentmap = potal[player.currentmap].nextmap;

}



void selectmap() {
    if (player.currentmap == 0) {
        map1_0();
    }

    else if (player.currentmap == 1) {
        map1_1();
    }
}

void drawPotal()
{
    setCursorPosition(potal[player.currentmap].pos.x, potal[player.currentmap].pos.y);
    printf("T");
}