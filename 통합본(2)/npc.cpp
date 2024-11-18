#include <stdio.h>
#include "npc.h"

NpcData npcList[MAX_NPC];		 //�迭 ����
NpcData* currentNPC = NULL;       // ������ ����

void initializeNpc()
{
	npcList[0] = { "�� ����", true, {5, 3}, Nobody };
	npcList[1] = { "���ȯ", true, {7, 3}, VolunArmy };
	npcList[2] = { "������", true, {9, 3}, GoverArmy };
	npcList[3] = { "�����", true, {11, 3}, JapArmy };
	npcList[4] = { "�� �ƹ���", true, {13, 3}, Nobody2 };
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