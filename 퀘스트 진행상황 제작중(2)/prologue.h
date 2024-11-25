#ifndef PROLOGUE_H
#define PROLOGUE_H

#include "utility.h"
#include "prologuemap.h"
#include "player.h"
#include "initmap.h"
#include "log.h"

typedef struct
{
	char name[50];
	int currentmap;
	int nextmap;
	Position pos;
	Position playerNextPos;
}Potal_prologue;

extern int mapLogShown[3];

void selectPrologueMap();
void displayMap_Prologue();
void showTutorial();
void drawPotal_prologue();
void gotoNextMapPrologue();

int encountPotal_prologue();
void encountPotal_prologueChoice();

#endif // !PROLOGUE_H
