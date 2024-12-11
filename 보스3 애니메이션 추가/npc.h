#ifndef NPC_H
#define NPC_H

#include "utility.h"
#include "player.h"
#define MAX_NPC 20

typedef enum {
	VolunArmy,	//의병
	GoverArmy,	//관군
	JapArmy,	//왜군
	Nobody,		//무소속
} NpcType;

typedef struct
{
	char name[100];
	bool hasQuest;
	int currentmap;
	int isActive;
	Position pos;
	NpcType type;
} NpcData;

extern NpcData npcList[MAX_NPC];
extern NpcData* currentNPC;

void initializeNpc();
void drawNpc(NpcData* npcList);
void ActiveNpc();

#endif // !NPC_H
