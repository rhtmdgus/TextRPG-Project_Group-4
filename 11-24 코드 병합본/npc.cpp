#include <stdio.h>
#include "npc.h"

NpcData npcList[MAX_NPC];		 //배열 정의
NpcData* currentNPC = NULL;       // 포인터 정의

void initializeNpc()
{
	npcList[0] = { "장 돌쇠", true, 0, {5, 3}, Nobody };
	npcList[1] = { "김두환", true, 0, {7, 3}, VolunArmy };
	npcList[2] = { "조병옥", true, 0, {9, 3}, GoverArmy };
	npcList[3] = { "나까무라", true, 0, {11, 3}, JapArmy };
	npcList[4] = { "김 아무개", true, 0, {13, 3}, Nobody };
	npcList[5] = { "이정재", true, 0, {8, 4}, VolunArmy };
	npcList[6] = { "장택상", true, 0, {10, 4}, GoverArmy };
	npcList[7] = { "미와 와사부로", true, 0, {12, 4}, JapArmy };
}

void drawNpc(NpcData* npcList)
{
	for (int i = 0; i < MAX_NPC; i++)
	{
		if(player.currentmap == (npcList + i)->currentmap)
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
}