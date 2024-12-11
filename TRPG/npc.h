#ifndef NPC_H
#define NPC_H

#include "utility.h"
#include "player.h"
#define MAX_NPC 20

typedef enum {
	VolunArmy,	//�Ǻ�
	GoverArmy,	//����
	JapArmy,	//�ֱ�
	Nobody,		//���Ҽ�
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
