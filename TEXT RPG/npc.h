#ifndef NPC_H
#define NPC_H

#include "utility.h"
#define MAX_NPC 5

typedef enum {
	VolunArmy,	//�Ǻ�
	GoverArmy,	//����
	JapArmy,	//�ֱ�
	Nobody		//���Ҽ�
} NpcType;

typedef struct
{
	char name[100];
	bool hasQuest;
	Position pos;
	NpcType type;
} NpcData;

extern NpcData npcList[MAX_NPC];
extern NpcData* currentNPC;

void initializeNpc();
void drawNpc(NpcData* npcList);

#endif // !NPC_H
