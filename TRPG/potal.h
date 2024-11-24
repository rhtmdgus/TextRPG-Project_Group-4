#ifndef POTAL_H
#define POTAL_H

#include "utility.h"
#include "selectmap.h"
#include "initmap.h"
#include "player.h"
#include "encount.h"



typedef struct
{

	char name[50];
	int currentmap;
	int nextmap;
	Position pos;


}Potal;

extern Potal potal[20];





void gotoNextMap();

void selectmap();
void drawPotal();







#endif // POTAL_H