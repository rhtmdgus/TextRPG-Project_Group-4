#ifndef NPC_H
#define NPC_H

#include "utility.h"
#include "player.h"
#define MAX_NPC 5

typedef enum {
	VolunArmy,	//狼捍
	GoverArmy,	//包焙
	JapArmy,	//恐焙
	Nobody,		//公家加
	Nobody2		//公家加2
} NpcType;

typedef struct
{
	char name[100];
	bool hasQuest;
	int currentmap;
	Position pos;
	NpcType type;
} NpcData;

extern NpcData npcList[MAX_NPC];
extern NpcData* currentNPC;

void initializeNpc();
void drawNpc(NpcData* npcList);

#endif // !NPC_H
