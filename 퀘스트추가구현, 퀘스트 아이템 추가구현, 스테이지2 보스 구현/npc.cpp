#include <stdio.h>
#include "npc.h"

NpcData npcList[MAX_NPC];		 //배열 정의
NpcData* currentNPC = NULL;       // 포인터 정의

void initializeNpc()
{
	npcList[0] = { "장 돌쇠", true, 0, 1, {31, 2}, Nobody };
	npcList[1] = { "김두환", true, 0, 1,{56, 3}, VolunArmy };
	npcList[2] = { "조병옥", true, 0, 1, {3, 27}, GoverArmy };
	npcList[3] = { "나까무라", true, 0, 1, {36, 2}, JapArmy };
	npcList[4] = { "김 아무개", true, 0, 1, {28, 14}, Nobody };
	npcList[5] = { "이정재", true, 0, 1, {33, 13}, VolunArmy };
	npcList[6] = { "장택상", true, 0, 1, {88, 2}, GoverArmy };
	npcList[7] = { "미와 와사부로", true, 0, 0, {9,27}, JapArmy };
	npcList[8] = { "김일동", true, 1, 1, {5, 5}, Nobody };
	npcList[9] = { "고돌쇠", true, 1, 1, {7, 5}, Nobody };
	npcList[10] = { "김영태", true, 1, 1, {9, 5}, VolunArmy };
	npcList[11] = { "김무옥", true, 1, 1, {11, 5}, VolunArmy };
	npcList[12] = { "문영철", true, 1, 1, {13, 15}, VolunArmy };
	npcList[13] = { "조개옥", true, 1, 0, {9, 5}, GoverArmy };
	npcList[14] = { "김종원", true, 1, 0, {11, 5}, GoverArmy };
	npcList[15] = { "김창룡", true, 1, 0, {13, 5}, GoverArmy };
	npcList[16] = { "마에다", true, 1, 0, {9, 5}, JapArmy };
	npcList[17] = { "아사노", true, 1, 0, {11, 5}, JapArmy };
	npcList[18] = { "마쓰라", true, 1, 0, {13, 5}, JapArmy };

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
			if((npcList+i)->isActive)
				printf("N");
			setColor(7);
		}
	}
}