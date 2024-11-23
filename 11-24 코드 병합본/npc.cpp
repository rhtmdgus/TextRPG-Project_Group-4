#include <stdio.h>
#include "npc.h"

NpcData npcList[MAX_NPC];		 //�迭 ����
NpcData* currentNPC = NULL;       // ������ ����

void initializeNpc()
{
	npcList[0] = { "�� ����", true, 0, {5, 3}, Nobody };
	npcList[1] = { "���ȯ", true, 0, {7, 3}, VolunArmy };
	npcList[2] = { "������", true, 0, {9, 3}, GoverArmy };
	npcList[3] = { "�����", true, 0, {11, 3}, JapArmy };
	npcList[4] = { "�� �ƹ���", true, 0, {13, 3}, Nobody };
	npcList[5] = { "������", true, 0, {8, 4}, VolunArmy };
	npcList[6] = { "���û�", true, 0, {10, 4}, GoverArmy };
	npcList[7] = { "�̿� �ͻ�η�", true, 0, {12, 4}, JapArmy };
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