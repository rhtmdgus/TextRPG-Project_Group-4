#ifndef POTAL_H
#define POTAL_H


#define MAP_WIDTH 100
#define MAP_HEIGHT 30
#define PANEL_WIDTH 30

#include "utility.h"
#include "selectmap.h"
#include "initmap.h"
#include "player.h"


typedef struct
{

	char name[20];
	int currentmap;
	int nextmap;


	Position pos;


}Potal;

extern Potal potal[20] = {

	{"1-1 -> 1-2", 1, 2, {98, 2}}, {"1-2 -> 1-3", 2, 3, {98, 2}}, {"1-3 -> 1-4", 3, 4, {98, 2}}

};








#endif // POTAL_H