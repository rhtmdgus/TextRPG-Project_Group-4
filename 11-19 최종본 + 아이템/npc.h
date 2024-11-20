#ifndef NPC_H
#define NPC_H

#include "utility.h"
#include "player.h"
#define MAX_NPC 5

typedef enum {
	VolunArmy,	//�Ǻ�
	GoverArmy,	//����
	JapArmy,	//�ֱ�
	Nobody,		//���Ҽ�
	Nobody2		//���Ҽ�2
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
