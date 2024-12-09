#include <stdio.h>
#include "npc.h"
#include "player.h"

NpcData npcList[MAX_NPC];		 //�迭 ����
NpcData* currentNPC = NULL;       // ������ ����

void initializeNpc()
{
	npcList[0] = { "�� ����", true, 0, 1, {31, 2}, Nobody };
	npcList[1] = { "���ȯ", true, 0, 1,{56, 3}, VolunArmy };
	npcList[2] = { "������", true, 0, 1, {3, 27}, GoverArmy };
	npcList[3] = { "�����", true, 0, 1, {36, 2}, JapArmy };
	npcList[4] = { "�� �ƹ���", true, 0, 1, {28, 14}, Nobody };
	npcList[5] = { "������", true, 0, 1, {33, 13}, VolunArmy };
	npcList[6] = { "���û�", true, 0, 1, {88, 2}, GoverArmy };
	npcList[7] = { "�̿� �ͻ�η�", true, 0, 0, {9,27}, JapArmy };
	npcList[8] = { "���ϵ�", true, 1, 1, {3, 5}, Nobody };
	npcList[9] = { "����", true, 1, 1, {12, 4}, Nobody };
	npcList[10] = { "�迵��", true, 1, 0, {20, 4}, VolunArmy };
	npcList[11] = { "�蹫��", true, 1, 0, {78, 18}, VolunArmy };
	npcList[12] = { "����ö", true, 1, 0, {64, 26}, VolunArmy };
	npcList[13] = { "������", true, 1, 0, {20, 4}, GoverArmy };
	npcList[14] = { "������", true, 1, 0, {78, 18}, GoverArmy };
	npcList[15] = { "��â��", true, 1, 0, {64, 26}, GoverArmy };
	npcList[16] = { "������", true, 1, 0, {20, 4}, JapArmy };
	npcList[17] = { "�ƻ��", true, 1, 0, {78, 18}, JapArmy };
	npcList[18] = { "������", true, 1, 0, {64, 26}, JapArmy };
}

void ActiveNpc()
{
	if (player.JRelationship >= player.WRelationship && player.JRelationship >= player.RRelationship)
	{
		npcList[13].isActive = 1;
		npcList[14].isActive = 1;
		npcList[15].isActive = 1;
	}
	else if (player.RRelationship >= player.WRelationship && player.RRelationship >= player.JRelationship)
	{
		npcList[10].isActive = 1;
		npcList[11].isActive = 1;
		npcList[12].isActive = 1;
	}
	else if (player.WRelationship >= player.RRelationship && player.WRelationship >= player.JRelationship)
	{
		npcList[16].isActive = 1;
		npcList[17].isActive = 1;
		npcList[18].isActive = 1;
	}
	else
		return;
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