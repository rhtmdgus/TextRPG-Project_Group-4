#include <stdio.h>
#include "npc.h"

NpcData npcList[MAX_NPC];		 //�迭 ����
NpcData* currentNPC = NULL;       // ������ ����

void initializeNpc()
{
	npcList[0] = { "�� ����", true, 1, 1, {5, 3}, Nobody };
	npcList[1] = { "���ȯ", true, 1, 1,{7, 3}, VolunArmy };
	npcList[2] = { "������", true, 1, 1, {9, 3}, GoverArmy };
	npcList[3] = { "�����", true, 1, 1, {11, 3}, JapArmy };
	npcList[4] = { "�� �ƹ���", true, 1, 1, {13, 3}, Nobody };
	npcList[5] = { "������", true, 0, 1, {33, 13}, VolunArmy };
	npcList[6] = { "���û�", true, 0, 1, {88, 2}, GoverArmy };
	npcList[7] = { "�̿� �ͻ�η�", true, 0, 0, {9,27}, JapArmy };
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