#include <stdio.h>
#include "npc.h"

NpcData npcList[MAX_NPC];		 //배열 정의
NpcData* currentNPC = NULL;       // 포인터 정의

void initializeNpc()
{
	npcList[0] = { "장 돌쇠", true, {5, 3}, Nobody };
	npcList[1] = { "김두환", true, {7, 3}, VolunArmy };
	npcList[2] = { "조병옥", true, {9, 3}, GoverArmy };
	npcList[3] = { "나까무라", true, {11, 3}, JapArmy };
	npcList[4] = { "김 아무개", true, {13, 3}, Nobody2 };
}

void drawNpc(NpcData* npcList)
{
	initializeNpc();
	for (int i = 0; i < MAX_NPC; i++)
	{
		setCursorPosition((npcList + i)->pos.x, (npcList + i)->pos.y);
		if ((npcList + i)->type == Nobody)
			setColor(7);
		else if ((npcList + i)->type == GoverArmy)
			setColor(2);
		else if ((npcList + i)->type == JapArmy)
			setColor(4);
		else if ((npcList + i)->type == VolunArmy)
			setColor(3);
		printf("N");
		setColor(7);
	}
}