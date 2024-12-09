#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "quest.h"
#include "player.h"
#include "displaymap.h"
#include "utility.h"
#include "questmanager.h"
#include "item.h"

Quest quest[MAX_QUEST];
PrologueQuest prologuequest; //���ѷα� ����Ʈ
QuestItemData QuestItemList[MAX_QUESTITEM];
QuestItemData* currentQuestItem = NULL;
int checkboss1 = 0;
int checkboss2 = 0;
int checkboss3 = 0;

void initializeQuest()
{
	quest[0] = { "��Ǭ �ݼ�",
	"��� �츮�� �� ġ�� ��Ǭ�� �ֽð�",
	0, 0, "�ʹ��ϱ���", "�ڳ׵� ���� ���°ǰ�?", "���� ����! �� ������ ���������� ���� �ʰڳ�" , 0, 1 };
	quest[1] = { "�ķ��� Ȯ���϶�",
	"�ķ��� �����ѵ� �ķ��� ���ش��ټ� �ְڳ�?",
	0, 0, "�Ǻ��� �� �ο��� ���￡�� �̱�� ���ε�..","���� �ķ��� ���ؿ��� �ʾҳ�?", "����! �ݵ�� �¸��ϰ� ���ڳ�" , 0, 1 };
	quest[2] = { "�ֱ��� �׿���",
	"���� ��Ȳ�� �Ҹ��ϴ�. �ֱ� 5���� ���̰�.",
	0, 0, "�츮���� ����� ���ΰ�?", "���� 5���� ������ ���߳�?", "�ڳ� ���п� ���￡�� ���������ٳ�." , 1, 5 };
	quest[3] = { "������ ���� ������ ���Ķ�",
	"������ ¬©�ϰ� ���״� ��������� ���� ������ ���Ŀ�!",
	0, 0, "�ʵ� �ᱹ�� �������̷α�!", "���� �������� ��ġ�� ���߳�?", "����! ���� �ֱ����ٴ� ������! ųųų" , 0, 1 };
	quest[4] = { "�뵿�� �����ְ�",
	"���� ������ ���� ���Ҵµ� �����ټ� �ְڳ�?",
	0, 0, "���� �����γ��� ���� ��ƾ���..", "���� ������ ġ���� ���߳�?", "����! �������� ���� ����� ��Ź�Ұ�" , 0, 1 };
	quest[5] = { "�λ���� �Ǻ�",
	"�ű� ���� �ֳ�? ���ļ� �����ϼ��� ���µ� �� �����ְ�",
	0, 0, "(�Ǻ��� ����Ͽ���)", " ", "���п� ��Ҵٳ�, �Ǻ����� ���״� ��������� ������ �ʰڳ� ? " , 0, 1 };
	quest[6] = { "���� �屺���� ����",
	"�ű� �ڳ�, �ֱ� ���ο� �ο�� �ִµ� �� �����ټ� �ְڳ�?",
	0, 0, "�ο��� ���ϳ� ����.. �˰ڳ�", "�� ���� �ִ°�?", "����! �ڳ� ���� �¸��Ҽ� �־���, �ڳ� ���� �� ������" , 0, 1 };
	quest[7] = { "�ֱ� ���ο��� ����",
	"�̺� �ڳ�! �� Ǯ���ָ� ���� �ֵ��� ����",
	0, 0, "��ȸ�ϰ� �ɰž�", "�� �ٹ��Ÿ��� �ž�?", "Ź���� �����̳�" , 0, 1 };
	quest[8] = { "�ļ� ����",
	"�ű� �ڳ� Ȥ�� �� �ϳ� ������ �� �ټ� �ְڳ�?",
	0, 0, "���� �ʹ� ������..�ƽ���", "���� ���� ���°�?", "����, ���� �ٽ� ���Ϸ� ���߰ڱ�" , 0, 1 }; // ���
	quest[9] = { "�� ��Ȯ",
	"���� ��Ȯ�Ϸ��µ� �ϼ��� ������, �� �����ټ� �ְڳ�?",
	0, 0, "�����ָ� �� �������״� ��Ź�ϳ�", "���� �� ������ �� �����ΰ�?", "�̰ɷ� �̹��ִ� ���� ��ƿ�� �ְھ�, ���� �� ��������" , 0, 1 }; // ���
	quest[10] = { "�ֱ� ó��",
	"���� ���� �ֱ��� �׿��µ� ��� �����ǰ� �־�, �� �����ְ�",
	0, 0, "�� �����ְ�, ������ ���� ������ ���� �ʰڳ�?", "���� �� ���� �ִ°�?", "�̷μ� �Ѽ� �����پ�.. ����" , 1, 5 }; // �Ǻ�
	quest[11] = { "�ֱ� �ķ�â�� ����",
	"�ֱ��� �ķ�â�� ��ġ ø���� ���Գ�, ���� ������ ���ֹ�����",
	0, 0, "�ķ�â�� �����ؾ� ���� Ʈ�δٳ�", "���� �Ϸ����� ���߳�?", "�̷μ� ����� ��Ⱑ ������ �ɼ�, ���ٳ�" , 0, 1 };// �Ǻ�
	quest[12] = { "�屺 ó��",
	"�տ� �츮�� ���θ��� ���� �ִٳ�, �� �����ְ�",
	0, 0, "���� ó������ �ʰ��� ������ �� ����", "���� ó������ ���߳�?", "���� ���� ���ȱ�, ����" , 0, 1 };// �Ǻ�
	quest[13] = { "�ֱ� ó��",
	"�ֱ� ���信�� ��� ������ �����ֳ�, �ڳ׵� ���Գ�",
	0, 0, "������ ���� �ſ��� ���ΰ�?", "���� �Ϸ����� ���߳�?", "����, �ڳ״��� �츮�� �켼�ϰ� �ɰɼ�" , 1, 5 };// ����
	quest[14] = { "���� ����",
	"������ ������� ���ڰ� ������, �Ĺ濡�� ���� �޾� ���Գ�",
	0, 0, "���޹��� ������ ������ �̾�� ����!", "���� �������� ���߳�?", "����, ��� �ο�� �ְھ�" , 0, 1 };// ����
	quest[15] = { "���� ó��",
	"�տ� ���θ��� ������ ������? ���� ó���ϼ�",
	0, 0, "ó������ ������ ���̻� �ο�� ����!", "���� ó������ ���߳�?", "����, ��� ���ư���" , 0, 1 };// ����
	quest[16] = { "�� �ŷ�",
	"�ļ��� ������ �ֳ�? �ָ� ���� ����",
	0, 0, "���� ����", "���� �������� ���߳�?", "�ÿ��ϱ�, ���� ����� ���̴�." , 0, 1 };// �ֱ�
	quest[17] = { "��Ż�� ��ǰ ����",
	"���� �鼺�� ��Ż�ؼ� ����� ��ǰ�� �ʹ� ���Ƽ� �� ���Գ�, �� ������",
	0, 0, "�ʹ� ���ڰԸ� �������� ����, �� ������", "���� �� ���Գ�?", "¬���ϱ���, ���� �� �ְڳ�" , 0, 1 };// �ֱ�
	quest[18] = { "�屺 ó��",
	"�츱 ���Դ� �������̱���? ���� ó���� �����ְ�",
	0, 0, "�����ָ� �츮�� �ڸ� �˾ƺ�����", "���� ó������ ���߳�?", "�ڳ״� ���� �ֱ��屺�� �ɰž�" , 0, 1 };// �ֱ�
	quest[18] = { "�������� ����",
	"���� �׳��� �� ���տ� �ִ�. ������ ó������.",
	0, 0, " ", " ", "���� �׿���." , 0, 1 };// ���� ����Ʈ(������)
}
/*

void initializePrologueQuest()
{
	prologuequest = { "������ ����",
	"�Ӹ��� ������. �ֱ������� ������ �ް� �����߾��� ����.",
	"�Ƴ���, �ֱ����� ���ѵ��ϴ�", "�ֱ��� �뼭�� �� ����. ������ �Ϸ�����" };
}  */

void initializeQuestItem()
{
	QuestItemList[0] = { "����", 0, 1, {2, 18}, VolunArmyQ };
	QuestItemList[1] = { "���� ����", 0, 1, {19, 27} , JapArmyQ };
	QuestItemList[2] = { "����", 0, 1, {34, 14} , NobodyQ };
	QuestItemList[3] = { "�ֱ� �ķ� â��", 1, 0, {51, 23}, VolunArmyQ };
	QuestItemList[4] = { "��Ż�� ��ǰ", 1, 0, {5, 2} , JapArmyQ };
	QuestItemList[5] = { "���� ����", 1, 0, {3, 13} , GoverArmyQ };
	QuestItemList[6] = { "��", 1, 1, {1, 9} , NobodyQ };
}

void ActiveQuestItem()
{

	if (player.JRelationship >= player.WRelationship && player.JRelationship >= player.RRelationship)
		QuestItemList[5].isActive = 1;
	else if (player.RRelationship >= player.WRelationship && player.RRelationship >= player.JRelationship)
		QuestItemList[3].isActive = 1;
	else if (player.WRelationship >= player.RRelationship && player.WRelationship >= player.JRelationship)
		QuestItemList[4].isActive = 1;
	else
		return;
}

void drawQuestItem(QuestItemData* QuestItemList)
{
	for (int i = 0; i < MAX_QUESTITEM; i++)
	{
		if (player.currentmap == (QuestItemList + i)->currentmap)
		{
			setCursorPosition((QuestItemList + i)->pos.x, (QuestItemList + i)->pos.y);
			if ((QuestItemList + i)->type == Nobody)
				setColor(7);
			else if ((QuestItemList + i)->type == GoverArmy)
				setColor(2);
			else if ((QuestItemList + i)->type == JapArmy)
				setColor(4);
			else if ((QuestItemList + i)->type == VolunArmy)
				setColor(3);
			if ((QuestItemList + i)->isActive)
				printf("Q");
			setColor(7);
		}
	}
}

void QuestComplete1() {
	if (player.money > 1)
	{
		setCursorPosition(40, 11);
		printf("���迡�� 1���� �ٱ�?");
		setCursorPosition(40, 12);
		printf("��ȭ��\n");
		setCursorPosition(40, 13);
		printf("1. �ش�\n");
		setCursorPosition(40, 14);
		printf("2. �� �� �����غ���\n");
		int num = _getch();
		if (num == '1')
		{
			quest[0].clear = 1;
			player.money--;
			player.RRelationship += 10;
			player.questmax--;
			Sleep(100);
			clearScreen();
			setCursorPosition(40, 11);
			printf(quest[0].description4);
			setCursorPosition(40, 12);
			printf("��ȭ��\n");
			setCursorPosition(40, 13);
			printf("1. �� �����ÿ�\n");
			updateLog("����Ʈ�� Ŭ���� �߽��ϴ�!");
			completeQuest(0);
			backToDialogue();
		}
		else
		{
			Sleep(100);
			clearScreen();
			setCursorPosition(40, 11);
			printf(quest[0].description3);
			setCursorPosition(40, 12);
			printf("��ȭ��\n");
			setCursorPosition(40, 13);
			printf("1. �̾��Ͽ�\n");
			backToDialogue();
		}
	}
	else
	{
		Sleep(100);
		clearScreen();
		setCursorPosition(40, 11);
		printf("���� ��� �̼��� Ŭ�����Ҽ� ����.");
		setCursorPosition(40, 12);
		printf("���� ������ �ٽ� ������ ����.");
		backToDialogue();
	}
}


void QuestComplete2() {
	if (player.questitem1 == 1)
	{
		setCursorPosition(40, 11);
		printf("�ķ��� �ٱ�?");
		setCursorPosition(40, 12);
		printf("��ȭ��\n");
		setCursorPosition(40, 13);
		printf("1. �ش�\n");
		setCursorPosition(40, 14);
		printf("2. �� �� �����غ���\n");
		int num = _getch();
		if (num == '1')
		{
			quest[1].clear = 1;
			player.questitem1 = 0;
			player.RRelationship += 20;
			player.questmax--;
			Sleep(100);
			clearScreen();
			setCursorPosition(40, 11);
			printf(quest[1].description4);
			setCursorPosition(40, 12);
			printf("��ȭ��\n");
			setCursorPosition(40, 13);
			printf("1. �����ÿ�\n");
			updateLog("����Ʈ�� Ŭ���� �߽��ϴ�!");
			updateLog("���⸦ ȹ���Ͽ����ϴ�!");
			updateLog("��� ȹ���Ͽ����ϴ�!");
			weaponchange(2);
			equipmentchange(2);
			completeQuest(1);
			backToDialogue();
		}
		else
		{
			Sleep(100);
			clearScreen();
			setCursorPosition(40, 11);
			printf(quest[1].description3);
			setCursorPosition(40, 12);
			printf("��ȭ��\n");
			setCursorPosition(40, 13);
			printf("1. �̾��Ͽ�\n");
			backToDialogue();
		}
	}
	else
	{
		Sleep(100);
		clearScreen();
		setCursorPosition(40, 11);
		printf("�ķ��� ��� �̼��� Ŭ�����Ҽ� ����.");
		setCursorPosition(40, 12);
		printf("�ķ��� �����ϰ� �ٽ� ������ ����.");
		backToDialogue();
	}
}


void QuestComplete3() {
	if (player.killcount >= 5)
	{
		setCursorPosition(40, 11);
		printf("�������� ����Ʈ�� �Ϸ��ߴٰ� ���ұ�?");
		setCursorPosition(40, 12);
		printf("��ȭ��\n");
		setCursorPosition(40, 13);
		printf("1. ���Ѵ�\n");
		setCursorPosition(40, 14);
		printf("2. ���߿� ����\n");
		int num = _getch();
		if (num == '1')
		{
			quest[2].clear = 1;
			player.killcount = 0;
			player.JRelationship += 30;
			player.WRelationship -= 50;
			player.money += 20;
			player.questmax--;
			Sleep(100);
			clearScreen();
			setCursorPosition(40, 11);
			printf(quest[2].description4);
			setCursorPosition(40, 12);
			printf("��ȭ��\n");
			setCursorPosition(40, 13);
			printf("1. �¸��ϱ� �ٶ��\n");
			updateLog("����Ʈ�� Ŭ���� �߽��ϴ�!");
			updateLog("���⸦ ȹ���Ͽ����ϴ�!");
			updateLog("��� ȹ���Ͽ����ϴ�!");
			weaponchange(2);
			equipmentchange(2);
			completeQuest(2);
			backToDialogue();
		}
		else
		{
			Sleep(100);
			clearScreen();
			setCursorPosition(40, 11);
			printf(quest[2].description3);
			setCursorPosition(40, 12);
			printf("��ȭ��\n");
			setCursorPosition(40, 13);
			printf("1. �̾��Ͽ�\n");
			backToDialogue();
		}
	}
	else
	{
		Sleep(100);
		clearScreen();
		setCursorPosition(40, 11);
		printf("���� ����� ���� �ֱ��� ������ ���ߴ�.");
		setCursorPosition(40, 12);
		printf("�ֱ��� ���� �� �����ϰ� ������ ����.");
		backToDialogue();
	}
}


void QuestComplete4() {
	if (player.questitem2 == 1)
	{
		setCursorPosition(40, 11);
		printf("�ֱ����� ���������� �ѱ��?");
		setCursorPosition(40, 12);
		printf("��ȭ��\n");
		setCursorPosition(40, 13);
		printf("1. �ش�\n");
		setCursorPosition(40, 14);
		printf("2. �� �� �����غ���\n");
		int num = _getch();
		if (num == '1')
		{
			quest[3].clear = 1;
			player.questitem2 = 0;
			player.WRelationship += 30;
			player.JRelationship -= 30;
			player.RRelationship -= 30;
			player.money += 30;
			player.questmax--;
			Sleep(100);
			clearScreen();
			setCursorPosition(40, 11);
			printf(quest[3].description4);
			setCursorPosition(40, 12);
			printf("��ȭ��\n");
			setCursorPosition(40, 13);
			printf("1. �� �����ÿ�\n");
			updateLog("����Ʈ�� Ŭ���� �߽��ϴ�!");
			updateLog("���⸦ ȹ���Ͽ����ϴ�!");
			updateLog("��� ȹ���Ͽ����ϴ�!");
			weaponchange(3);
			equipmentchange(3);
			completeQuest(3);
			backToDialogue();
		}
		else
		{
			Sleep(100);
			clearScreen();
			setCursorPosition(40, 11);
			printf(quest[3].description3);
			setCursorPosition(40, 12);
			printf("��ȭ��\n");
			setCursorPosition(40, 13);
			printf("1. �̾��Ͽ�\n");
			backToDialogue();
		}
	}
	else
	{
		Sleep(100);
		clearScreen();
		setCursorPosition(40, 11);
		printf("���� ������ ��� �̼��� Ŭ�����Ҽ� ����.");
		setCursorPosition(40, 12);
		printf("���� ������ ��ġ�� �ٽ� ������ ����.");
		backToDialogue();
	}
}


void QuestComplete5() {
	if (player.questitem3 == 1)
	{
		setCursorPosition(40, 11);
		printf("�ӹ��� �Ϸ��ұ�?");
		setCursorPosition(40, 12);
		printf("��ȭ��\n");
		setCursorPosition(40, 13);
		printf("1. �Ϸ��Ѵ�\n");
		setCursorPosition(40, 14);
		printf("2. ���߿� �Ϸ�����.\n");
		int num = _getch();
		if (num == '1')
		{
			quest[4].clear = 1;
			player.questitem3 = 0;
			player.RRelationship += 10;
			player.questmax--;
			Sleep(100);
			clearScreen();
			setCursorPosition(40, 11);
			printf(quest[4].description4);
			setCursorPosition(40, 12);
			printf("��ȭ��\n");
			setCursorPosition(40, 13);
			printf("1. �� �����ÿ�\n");
			updateLog("����Ʈ�� Ŭ���� �߽��ϴ�!");
			completeQuest(4);
			backToDialogue();
		}
		else
		{
			Sleep(100);
			clearScreen();
			setCursorPosition(40, 11);
			printf(quest[4].description3);
			setCursorPosition(40, 12);
			printf("��ȭ��\n");
			setCursorPosition(40, 13);
			printf("1. �̾��Ͽ�\n");
			backToDialogue();
		}
	}
	else
	{
		Sleep(100);
		clearScreen();
		setCursorPosition(40, 11);
		printf("���� ���� ġ���� �ʾ� �̼��� Ŭ�����Ҽ� ����.");
		setCursorPosition(40, 12);
		printf("���� ġ��� �ٽ� ������ ����.");
		backToDialogue();
	}
}

void QuestComplete6() {
	if (checkboss1 == 1)
	{
		setCursorPosition(40, 11);
		printf("�ӹ��� �Ϸ��ұ�?");
		setCursorPosition(40, 12);
		printf("��ȭ��\n");
		setCursorPosition(40, 13);
		printf("1. �Ϸ��Ѵ�\n");
		setCursorPosition(40, 14);
		printf("2. ���߿� �Ϸ�����.\n");
		int num = _getch();
		if (num == '1')
		{
			quest[6].clear = 1;
			player.questitem1 = 0;
			player.JRelationship += 20;
			player.questmax--;
			npcList[7].isActive = 1;
			checkboss1 = 0;
			checkboss2 = 0;
			checkboss3 = 0;
			potal[player.currentmap].spawnPotal = true;
			Sleep(100);
			clearScreen();
			setCursorPosition(40, 11);
			printf(quest[6].description4);
			setCursorPosition(40, 12);
			printf("��ȭ��\n");
			setCursorPosition(40, 13);
			printf("1. �����̿�\n");
			updateLog("����Ʈ�� Ŭ���� �߽��ϴ�!");
			updateLog("���⸦ ȹ���Ͽ����ϴ�!");
			updateLog("��� ȹ���Ͽ����ϴ�!");
			weaponchange(3);
			equipmentchange(3);
			completeQuest(6);
			Sleep(200);
			displayLog();
			backToDialogue();
		}
		else
		{
			Sleep(100);
			clearScreen();
			setCursorPosition(40, 11);
			printf(quest[6].description3);
			setCursorPosition(40, 12);
			printf("��ȭ��\n");
			setCursorPosition(40, 13);
			printf("1. �̾��Ͽ�\n");
			backToDialogue();
		}
	}
	else
	{
		Sleep(100);
		clearScreen();
		setCursorPosition(40, 11);
		printf("���� �ֱ� ���θ� ���� ���Ͽ���.");
		setCursorPosition(40, 12);
		printf("�ֱ� ����� ��� �ٽ� ������ ����.");
		backToDialogue();
	}
}

void QuestComplete7() {
	if (quest[7].clear == 0)
	{
		setCursorPosition(40, 11);
		printf("�ֱ� ����� Ǯ���ٱ�?");
		setCursorPosition(40, 12);
		printf("��ȭ��\n");
		setCursorPosition(40, 13);
		printf("1. �Ϸ��Ѵ�\n");
		setCursorPosition(40, 14);
		printf("2. ���߿� �Ϸ�����.\n");
		int num = _getch();
		if (num == '1')
		{
			quest[7].clear = 1;
			player.WRelationship += 30;
			player.JRelationship -= 30;
			player.RRelationship -= 10;
			player.money += 20;
			player.questmax--;
			Sleep(100);
			clearScreen();
			setCursorPosition(40, 11);
			printf(quest[7].description4);
			setCursorPosition(40, 12);
			printf("��ȭ��\n");
			setCursorPosition(40, 13);
			printf("1. ���� ���ÿ�\n");
			updateLog("����Ʈ�� Ŭ���� �߽��ϴ�!");
			updateLog("���⸦ ȹ���Ͽ����ϴ�!");
			updateLog("��� ȹ���Ͽ����ϴ�!");
			weaponchange(4);
			equipmentchange(4);
			completeQuest(7);
			npcList[7].isActive = 0;
			Sleep(200);
			displayLog();
			backToMap();
		}
		else
		{
			Sleep(100);
			clearScreen();
			setCursorPosition(40, 11);
			printf(quest[7].description3);
			setCursorPosition(40, 12);
			printf("��ȭ��\n");
			setCursorPosition(40, 13);
			printf("1. ��ٷ����ÿ�\n");
			backToDialogue();
		}
	}
	else
	{
		Sleep(100);
		clearScreen();
		setCursorPosition(40, 11);
		printf("���� �ֱ� ����� Ǯ���� ������ ì���� ���ߴ�.");
		setCursorPosition(40, 12);
		printf("������ ì��� �ٽ� ������ ����.");
		backToDialogue();
	}
}
void QuestComplete8() {
	if (player.MPpotion >= 1)
	{
		setCursorPosition(40, 11);
		printf("���� ���� �Ѱ��� �ٱ�?");
		setCursorPosition(40, 12);
		printf("��ȭ��\n");
		setCursorPosition(40, 13);
		printf("1. �ش�\n");
		setCursorPosition(40, 14);
		printf("2. ���߿� ����\n");
		int num = _getch();
		if (num == '1')
		{
			quest[8].clear = 1;
			player.MPpotion--;
			player.RRelationship += 10;
			player.JRelationship += 10;
			player.questmax--;
			Sleep(100);
			clearScreen();
			setCursorPosition(40, 11);
			printf(quest[8].description4);
			setCursorPosition(40, 12);
			printf("��ȭ��\n");
			setCursorPosition(40, 13);
			printf("1. �� �����ÿ�\n");
			updateLog("����Ʈ�� Ŭ���� �߽��ϴ�!");
			updateLog("���⸦ ȹ���Ͽ����ϴ�!");
			updateLog("��� ȹ���Ͽ����ϴ�!");
			backToDialogue();
		}
		else
		{
			Sleep(100);
			clearScreen();
			setCursorPosition(40, 11);
			printf(quest[8].description3);
			setCursorPosition(40, 12);
			printf("��ȭ��\n");
			setCursorPosition(40, 13);
			printf("1. �̾��Ͽ�\n");
			backToDialogue();
		}
	}
	else
	{
		Sleep(100);
		clearScreen();
		setCursorPosition(40, 11);
		printf("���� ������ ��� �Ϸ��� �� ����.");
		setCursorPosition(40, 12);
		printf("�������� �����ϰ� ����.");
		backToDialogue();
	}
}
void QuestComplete9() {
	if (player.questitem1 == 1)
	{
		setCursorPosition(40, 11);
		printf("����Ʈ�� �Ϸ��ұ�?");
		setCursorPosition(40, 12);
		printf("��ȭ��\n");
		setCursorPosition(40, 13);
		printf("1. �Ϸ��Ѵ�\n");
		setCursorPosition(40, 14);
		printf("2. ���߿� ����\n");
		int num = _getch();
		if (num == '1')
		{
			quest[9].clear = 1;
			player.questitem1 = 0;
			player.RRelationship += 10;
			player.JRelationship += 10;
			player.questmax--;
			Sleep(100);
			clearScreen();
			setCursorPosition(40, 11);
			printf(quest[9].description4);
			setCursorPosition(40, 12);
			printf("��ȭ��\n");
			setCursorPosition(40, 13);
			printf("1. �� �����ÿ�\n");
			updateLog("����Ʈ�� Ŭ���� �߽��ϴ�!");
			completeQuest(9);
			backToDialogue();
		}
		else
		{
			Sleep(100);
			clearScreen();
			setCursorPosition(40, 11);
			printf(quest[9].description3);
			setCursorPosition(40, 12);
			printf("��ȭ��\n");
			setCursorPosition(40, 13);
			printf("1. �̾��Ͽ�\n");
			backToDialogue();
		}
	}
	else
	{
		Sleep(100);
		clearScreen();
		setCursorPosition(40, 11);
		printf("���� ���� ��Ȯ���� ���ߴ�.");
		setCursorPosition(40, 12);
		printf("���� ��Ȯ�ϰ� ����.");
		backToDialogue();
	}
}
void QuestComplete10() {
	if (player.killcount >= 5)
	{
		setCursorPosition(40, 11);
		printf("����Ʈ�� �Ϸ��ұ�?");
		setCursorPosition(40, 12);
		printf("��ȭ��\n");
		setCursorPosition(40, 13);
		printf("1. �Ϸ��Ѵ�\n");
		setCursorPosition(40, 14);
		printf("2. ���߿� ����\n");
		int num = _getch();
		if (num == '1')
		{
			quest[10].clear = 1;
			player.killcount = 0;
			player.RRelationship += 30;
			player.questmax--;
			Sleep(100);
			clearScreen();
			setCursorPosition(40, 11);
			printf(quest[10].description4);
			setCursorPosition(40, 12);
			printf("��ȭ��\n");
			setCursorPosition(40, 13);
			printf("1. �� �����ÿ�\n");
			updateLog("����Ʈ�� Ŭ���� �߽��ϴ�!");
			updateLog("���⸦ ȹ���Ͽ����ϴ�!");
			updateLog("��� ȹ���Ͽ����ϴ�!");
			weaponchange(4);
			equipmentchange(4);
			completeQuest(10);
			backToDialogue();
		}
		else
		{
			Sleep(100);
			clearScreen();
			setCursorPosition(40, 11);
			printf(quest[10].description3);
			setCursorPosition(40, 12);
			printf("��ȭ��\n");
			setCursorPosition(40, 13);
			printf("1. �̾��Ͽ�\n");
			backToDialogue();
		}
	}
	else
	{
		Sleep(100);
		clearScreen();
		setCursorPosition(40, 11);
		printf("���� ����� ���� ���� ������ ���ߴ�.");
		setCursorPosition(40, 12);
		printf("���� ���̰� �ٽ� ����.");
		backToDialogue();
	}
}
void QuestComplete11() {
	if (player.questitem2 == 1)
	{
		setCursorPosition(40, 11);
		printf("����Ʈ�� �Ϸ��ұ�?");
		setCursorPosition(40, 12);
		printf("��ȭ��\n");
		setCursorPosition(40, 13);
		printf("1. �Ϸ��Ѵ�\n");
		setCursorPosition(40, 14);
		printf("2. ���߿� ����\n");
		int num = _getch();
		if (num == '1')
		{
			quest[11].clear = 1;
			player.questitem2 = 0;
			player.RRelationship += 30;
			player.questmax--;
			Sleep(100);
			clearScreen();
			setCursorPosition(40, 11);
			printf(quest[11].description4);
			setCursorPosition(40, 12);
			printf("��ȭ��\n");
			setCursorPosition(40, 13);
			printf("1. �� �����ÿ�\n");
			updateLog("����Ʈ�� Ŭ���� �߽��ϴ�!");
			updateLog("���⸦ ȹ���Ͽ����ϴ�!");
			updateLog("��� ȹ���Ͽ����ϴ�!");
			weaponchange(4);
			equipmentchange(4);
			completeQuest(11);
			backToDialogue();
		}
		else
		{
			Sleep(100);
			clearScreen();
			setCursorPosition(40, 11);
			printf(quest[11].description3);
			setCursorPosition(40, 12);
			printf("��ȭ��\n");
			setCursorPosition(40, 13);
			printf("1. �̾��Ͽ�\n");
			backToDialogue();
		}
	}
	else
	{
		Sleep(100);
		clearScreen();
		setCursorPosition(40, 11);
		printf("���� �ķ�â�� �¿��� ���ߴ�.");
		setCursorPosition(40, 12);
		printf("�ķ�â�� �¿�� ����.");
		backToDialogue();
	}
}
void QuestComplete12() {
	if (checkboss2 == 1)
	{
		setCursorPosition(40, 11);
		printf("����Ʈ�� �Ϸ��ұ�?");
		setCursorPosition(40, 12);
		printf("��ȭ��\n");
		setCursorPosition(40, 13);
		printf("1. �Ϸ��Ѵ�\n");
		setCursorPosition(40, 14);
		printf("2. ���߿� ����\n");
		int num = _getch();
		if (num == '1')
		{
			quest[12].clear = 1;
			checkboss1 = 0;
			checkboss2 = 0;
			checkboss3 = 0;
			player.RRelationship += 50;
			player.money += 30;
			player.questmax--;
			potal[player.currentmap].spawnPotal = true;
			Sleep(100);
			clearScreen();
			setCursorPosition(40, 11);
			printf(quest[12].description4);
			setCursorPosition(40, 12);
			printf("��ȭ��\n");
			setCursorPosition(40, 13);
			printf("1. ���ô�\n");
			updateLog("����Ʈ�� Ŭ���� �߽��ϴ�!");
			updateLog("���⸦ ȹ���Ͽ����ϴ�!");
			updateLog("��� ȹ���Ͽ����ϴ�!");
			weaponchange(5);
			equipmentchange(5);
			completeQuest(12);
			backToDialogue();
		}
		else
		{
			Sleep(100);
			clearScreen();
			setCursorPosition(40, 11);
			printf(quest[12].description3);
			setCursorPosition(40, 12);
			printf("��ȭ��\n");
			setCursorPosition(40, 13);
			printf("1. �̾��Ͽ�\n");
			backToDialogue();
		}
	}
	else
	{
		Sleep(100);
		clearScreen();
		setCursorPosition(40, 11);
		printf("���� ������ óġ���� ���ߴ�.");
		setCursorPosition(40, 12);
		printf("������ óġ�ϰ� ����.");
		backToDialogue();
	}
}

void QuestComplete13() {
	if (player.killcount >= 5)
	{
		setCursorPosition(40, 11);
		printf("����Ʈ�� �Ϸ��ұ�?");
		setCursorPosition(40, 12);
		printf("��ȭ��\n");
		setCursorPosition(40, 13);
		printf("1. �Ϸ��Ѵ�\n");
		setCursorPosition(40, 14);
		printf("2. ���߿� ����\n");
		int num = _getch();
		if (num == '1')
		{
			quest[13].clear = 1;
			player.killcount = 0;
			player.JRelationship += 30;
			player.questmax--;
			Sleep(100);
			clearScreen();
			setCursorPosition(40, 11);
			printf(quest[13].description4);
			setCursorPosition(40, 12);
			printf("��ȭ��\n");
			setCursorPosition(40, 13);
			printf("1. �� �����ÿ�\n");
			updateLog("����Ʈ�� Ŭ���� �߽��ϴ�!");
			updateLog("���⸦ ȹ���Ͽ����ϴ�!");
			updateLog("��� ȹ���Ͽ����ϴ�!");
			weaponchange(4);
			equipmentchange(4);
			completeQuest(13);
			backToDialogue();
		}
		else
		{
			Sleep(100);
			clearScreen();
			setCursorPosition(40, 11);
			printf(quest[13].description3);
			setCursorPosition(40, 12);
			printf("��ȭ��\n");
			setCursorPosition(40, 13);
			printf("1. �̾��Ͽ�\n");
			backToDialogue();
		}
	}
	else
	{
		Sleep(100);
		clearScreen();
		setCursorPosition(40, 11);
		printf("���� ����� ���� ���� ������ ���ߴ�.");
		setCursorPosition(40, 12);
		printf("���� ���̰� �ٽ� ����.");
		backToDialogue();
	}
}

void QuestComplete14() {
	if (player.questitem2 == 1)
	{
		setCursorPosition(40, 11);
		printf("����Ʈ�� �Ϸ��ұ�?");
		setCursorPosition(40, 12);
		printf("��ȭ��\n");
		setCursorPosition(40, 13);
		printf("1. �Ϸ��Ѵ�\n");
		setCursorPosition(40, 14);
		printf("2. ���߿� ����\n");
		int num = _getch();
		if (num == '1')
		{
			quest[14].clear = 1;
			player.questitem2 = 0;
			player.JRelationship += 30;
			player.questmax--;
			Sleep(100);
			clearScreen();
			setCursorPosition(40, 11);
			printf(quest[14].description4);
			setCursorPosition(40, 12);
			printf("��ȭ��\n");
			setCursorPosition(40, 13);
			printf("1. �� �����ÿ�\n");
			updateLog("����Ʈ�� Ŭ���� �߽��ϴ�!");
			updateLog("���⸦ ȹ���Ͽ����ϴ�!");
			updateLog("��� ȹ���Ͽ����ϴ�!");
			weaponchange(4);
			equipmentchange(4);
			completeQuest(14);
			backToDialogue();
		}
		else
		{
			Sleep(100);
			clearScreen();
			setCursorPosition(40, 11);
			printf(quest[14].description3);
			setCursorPosition(40, 12);
			printf("��ȭ��\n");
			setCursorPosition(40, 13);
			printf("1. �̾��Ͽ�\n");
			backToDialogue();
		}
	}
	else
	{
		Sleep(100);
		clearScreen();
		setCursorPosition(40, 11);
		printf("���� ���ڸ� �������� ���ߴ�.");
		setCursorPosition(40, 12);
		printf("���ڸ� ������ ����.");
		backToDialogue();
	}
}

void QuestComplete15() {
	if (checkboss2 == 1)
	{
		setCursorPosition(40, 11);
		printf("����Ʈ�� �Ϸ��ұ�?");
		setCursorPosition(40, 12);
		printf("��ȭ��\n");
		setCursorPosition(40, 13);
		printf("1. �Ϸ��Ѵ�\n");
		setCursorPosition(40, 14);
		printf("2. ���߿� ����\n");
		int num = _getch();
		if (num == '1')
		{
			quest[15].clear = 1;
			checkboss1 = 0;
			checkboss2 = 0;
			checkboss3 = 0;
			player.JRelationship += 50;
			player.money += 30;
			player.questmax--;
			potal[player.currentmap].spawnPotal = true;
			Sleep(100);
			clearScreen();
			setCursorPosition(40, 11);
			printf(quest[15].description4);
			setCursorPosition(40, 12);
			printf("��ȭ��\n");
			setCursorPosition(40, 13);
			printf("1. ���ô�\n");
			updateLog("����Ʈ�� Ŭ���� �߽��ϴ�!");
			updateLog("���⸦ ȹ���Ͽ����ϴ�!");
			updateLog("��� ȹ���Ͽ����ϴ�!");
			weaponchange(5);
			equipmentchange(5);
			completeQuest(15);
			backToDialogue();
		}
		else
		{
			Sleep(100);
			clearScreen();
			setCursorPosition(40, 11);
			printf(quest[15].description3);
			setCursorPosition(40, 12);
			printf("��ȭ��\n");
			setCursorPosition(40, 13);
			printf("1. �̾��Ͽ�\n");
			backToDialogue();
		}
	}
	else
	{
		Sleep(100);
		clearScreen();
		setCursorPosition(40, 11);
		printf("���� ������ óġ���� ���ߴ�.");
		setCursorPosition(40, 12);
		printf("������ óġ�ϰ� ����.");
		backToDialogue();
	}
}

void QuestComplete16() {
	if (player.MPpotion >= 1)
	{
		setCursorPosition(40, 11);
		printf("���� ���� �Ѱ��� �ٱ�?");
		setCursorPosition(40, 12);
		printf("��ȭ��\n");
		setCursorPosition(40, 13);
		printf("1. �ش�\n");
		setCursorPosition(40, 14);
		printf("2. ���߿� ����\n");
		int num = _getch();
		if (num == '1')
		{
			quest[16].clear = 1;
			player.MPpotion--;
			player.WRelationship += 30;
			player.RRelationship -= 30;
			player.JRelationship -= 30;
			player.money += 20;
			player.questmax--;
			Sleep(100);
			clearScreen();
			setCursorPosition(40, 11);
			printf(quest[16].description4);
			setCursorPosition(40, 12);
			printf("��ȭ��\n");
			setCursorPosition(40, 13);
			printf("1. �� �����ÿ�\n");
			updateLog("����Ʈ�� Ŭ���� �߽��ϴ�!");
			updateLog("���⸦ ȹ���Ͽ����ϴ�!");
			updateLog("��� ȹ���Ͽ����ϴ�!");
			weaponchange(5);
			equipmentchange(5);
			completeQuest(16);
			backToDialogue();
		}
		else
		{
			Sleep(100);
			clearScreen();
			setCursorPosition(40, 11);
			printf(quest[16].description3);
			setCursorPosition(40, 12);
			printf("��ȭ��\n");
			setCursorPosition(40, 13);
			printf("1. �̾��Ͽ�\n");
			backToDialogue();
		}
	}
	else
	{
		Sleep(100);
		clearScreen();
		setCursorPosition(40, 11);
		printf("���� ������ ��� �Ϸ��� �� ����.");
		setCursorPosition(40, 12);
		printf("�������� �����ϰ� ����.");
		backToDialogue();
	}
}

void QuestComplete17() {
	if (player.questitem2 == 1)
	{
		setCursorPosition(40, 11);
		printf("����Ʈ�� �Ϸ��ұ�?");
		setCursorPosition(40, 12);
		printf("��ȭ��\n");
		setCursorPosition(40, 13);
		printf("1. �Ϸ��Ѵ�\n");
		setCursorPosition(40, 14);
		printf("2. ���߿� ����\n");
		int num = _getch();
		if (num == '1')
		{
			quest[17].clear = 1;
			player.questitem2 = 0;
			player.WRelationship += 30;
			player.JRelationship -= 30;
			player.RRelationship -= 30;
			player.money += 50;
			player.questmax--;
			Sleep(100);
			clearScreen();
			setCursorPosition(40, 11);
			printf(quest[17].description4);
			setCursorPosition(40, 12);
			printf("��ȭ��\n");
			setCursorPosition(40, 13);
			printf("1. �� �����ÿ�\n");
			updateLog("����Ʈ�� Ŭ���� �߽��ϴ�!");
			updateLog("���⸦ ȹ���Ͽ����ϴ�!");
			updateLog("��� ȹ���Ͽ����ϴ�!");
			weaponchange(6);
			equipmentchange(6);
			completeQuest(17);
			backToDialogue();
		}
		else
		{
			Sleep(100);
			clearScreen();
			setCursorPosition(40, 11);
			printf(quest[17].description3);
			setCursorPosition(40, 12);
			printf("��ȭ��\n");
			setCursorPosition(40, 13);
			printf("1. �̾��Ͽ�\n");
			backToDialogue();
		}
	}
	else
	{
		Sleep(100);
		clearScreen();
		setCursorPosition(40, 11);
		printf("���� ��Ż�� ��ǰ�� ������ ���� ���ߴ�");
		setCursorPosition(40, 12);
		printf("��Ż�� ��ǰ�� ������ ����.");
		backToDialogue();
	}
}

void QuestComplete18() {
	if (checkboss2 == 1)
	{
		setCursorPosition(40, 11);
		printf("����Ʈ�� �Ϸ��ұ�?");
		setCursorPosition(40, 12);
		printf("��ȭ��\n");
		setCursorPosition(40, 13);
		printf("1. �Ϸ��Ѵ�\n");
		setCursorPosition(40, 14);
		printf("2. ���߿� ����\n");
		int num = _getch();
		if (num == '1')
		{
			quest[18].clear = 1;
			checkboss2 = 0;
			player.WRelationship += 50;
			player.JRelationship -= 30;
			player.RRelationship -= 30;
			player.money += 100;
			player.questmax--;
			checkboss1 = 0;
			checkboss2 = 0;
			checkboss3 = 0;
			potal[player.currentmap].spawnPotal = true;
			Sleep(100);
			clearScreen();
			setCursorPosition(40, 11);
			printf(quest[18].description4);
			setCursorPosition(40, 12);
			printf("��ȭ��\n");
			setCursorPosition(40, 13);
			printf("1. ���ô�\n");
			updateLog("����Ʈ�� Ŭ���� �߽��ϴ�!");
			updateLog("���⸦ ȹ���Ͽ����ϴ�!");
			updateLog("��� ȹ���Ͽ����ϴ�!");
			weaponchange(7);
			equipmentchange(7);
			completeQuest(18);
			backToDialogue();
		}
		else
		{
			Sleep(100);
			clearScreen();
			setCursorPosition(40, 11);
			printf(quest[18].description3);
			setCursorPosition(40, 12);
			printf("��ȭ��\n");
			setCursorPosition(40, 13);
			printf("1. �̾��Ͽ�\n");
			backToDialogue();
		}
	}
	else
	{
		Sleep(100);
		clearScreen();
		setCursorPosition(40, 11);
		printf("���� ������ óġ���� ���ߴ�.");
		setCursorPosition(40, 12);
		printf("������ óġ�ϰ� ����.");
		backToDialogue();
	}
}

void QuestComplete19() {
	if (checkboss3 == 1)
	{
		setCursorPosition(40, 11);
		printf("����Ʈ�� �Ϸ��ұ�?");
		setCursorPosition(40, 12);
		printf("��ȭ��\n");
		setCursorPosition(40, 13);
		printf("1. �Ϸ��Ѵ�\n");
		setCursorPosition(40, 14);
		printf("2. ���߿� ����\n");
		int num = _getch();
		if (num == '1')
		{
			quest[19].clear = 1;
			checkboss2 = 0;
			player.questmax--;
			Sleep(100);
			clearScreen();
			setCursorPosition(40, 11);
			printf(quest[19].description4);
			setCursorPosition(40, 12);
			printf("��ȭ��\n");
			setCursorPosition(40, 13);
			printf("1. ��������\n");
			completeQuest(19);
			backToDialogue();
		}
		else
		{
			backToDialogue();
		}
	}
	else
	{
		Sleep(100);
		clearScreen();
		setCursorPosition(40, 11);
		printf("���� ���� óġ���� ���ߴ�.");
		setCursorPosition(40, 12);
		printf("���� óġ�ϰ� ����.");
		backToDialogue();
	}
}